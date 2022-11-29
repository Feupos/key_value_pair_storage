#pragma once

#include <boost/asio.hpp>
#include <memory>

#include "kvpstorage/request_handler.hpp"
#include "kvpstorage/storage_interface.hpp"

using boost::asio::ip::tcp;

static constexpr int MAX_LENGTH = 1024;

template<typename Acceptor = tcp::acceptor, typename Socket = tcp::socket>
class TcpServer : RequestHandler
{
 public:
  TcpServer(Acceptor& acceptor, Socket& socket, std::shared_ptr<StorageInterface> storage, unsigned short int port);

 private:
  void AcceptConnection();
  void ReadData();
  void WriteData(std::string data);
  void RestartConnection();

  char _buffer[MAX_LENGTH];
  Acceptor& _acceptor;
  Socket& _socket;
  unsigned short int _port;
};

template<typename Acceptor, typename Socket>
TcpServer<Acceptor, Socket>::TcpServer(Acceptor& acceptor, Socket& socket, std::shared_ptr<StorageInterface> storage, unsigned short int port)
    : RequestHandler(storage),
      _acceptor(acceptor),
      _socket(socket),
      _port(port)
{
  AcceptConnection();
}

template<typename Acceptor, typename Socket>
void TcpServer<Acceptor, Socket>::AcceptConnection()
{
  auto endpoint = tcp::endpoint(tcp::v4(), this->_port);
  _acceptor.open(endpoint.protocol());
  _acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
  _acceptor.bind(endpoint);
  _acceptor.listen();

  _acceptor.async_accept(_socket, [this](std::error_code ec) {
    if (!ec)
    {
      this->ReadData();
    }
    else
    {
      this->RestartConnection();
    }
  });
}

template<typename Acceptor, typename Socket>
void TcpServer<Acceptor, Socket>::ReadData()
{
  _socket.async_read_some(boost::asio::buffer(_buffer, MAX_LENGTH), [this](std::error_code ec, std::size_t length) {
    if (!ec)
    {
      std::string response = this->HandleRequest(std::string(static_cast<char*>(_buffer), length));
      this->WriteData(response);
    }
    else
    {
      this->RestartConnection();
    }
  });
}

template<typename Acceptor, typename Socket>
void TcpServer<Acceptor, Socket>::WriteData(std::string data)
{
  _socket.async_write_some(boost::asio::buffer(data), [this](std::error_code ec, std::size_t /*length*/) {
    if (!ec)
    {
      ReadData();
    }
    else
    {
      this->RestartConnection();
    }
  });
}

template<typename Acceptor, typename Socket>
void TcpServer<Acceptor, Socket>::RestartConnection()
{
  _acceptor.close();
  _socket.close();
  this->AcceptConnection();
}

typedef TcpServer<tcp::acceptor, tcp::socket> AsioTcpServer;