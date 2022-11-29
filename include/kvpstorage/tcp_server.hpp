#pragma once

#include <boost/asio.hpp>
#include <memory>

#include "kvpstorage/request_handler.hpp"
#include "kvpstorage/storage_interface.hpp"

using boost::asio::ip::tcp;

static constexpr int MAX_LENGTH = 1024;

template<typename Acceptor, typename Socket>
class TcpServer : RequestHandler
{
 public:
  TcpServer(Acceptor& acceptor, Socket& socket, std::shared_ptr<StorageInterface> storage);

 private:
  void AcceptConnection();
  void ReadData();
  void WriteData(std::string data);

  char _buffer[MAX_LENGTH];
  Acceptor& _acceptor;
  Socket& _socket;
};

template<typename Acceptor, typename Socket>
TcpServer<Acceptor, Socket>::TcpServer(Acceptor& acceptor, Socket& socket, std::shared_ptr<StorageInterface> storage)
    : RequestHandler(storage),
      _acceptor(acceptor),
      _socket(socket)
{
  AcceptConnection();
}

template<typename Acceptor, typename Socket>
void TcpServer<Acceptor, Socket>::AcceptConnection()
{
  _acceptor.async_accept(_socket, [this](std::error_code ec) {
    if (!ec)
    {
      this->ReadData();
    }

    AcceptConnection();
  });
}

template<typename Acceptor, typename Socket>
void TcpServer<Acceptor, Socket>::ReadData()
{
  _socket.async_read_some(boost::asio::buffer(_buffer, MAX_LENGTH), [this](std::error_code ec, std::size_t length) {
    if (!ec)
    {
      std::string response = this->HandleRequest(std::string(_buffer, length));
      this->WriteData(response);
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
  });
}

typedef TcpServer<tcp::acceptor, tcp::socket> AsioTcpServer;