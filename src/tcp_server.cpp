#include "kvpstorage/tcp_server.hpp"

TcpServer::TcpServer(asio::io_context& io_context, std::shared_ptr<StorageInterface> storage, short unsigned int port)
    : RequestHandler(storage),
      _acceptor(io_context, tcp::endpoint(tcp::v4(), port)),
      _socket(io_context)
{
  AcceptConnection();
}

void TcpServer::AcceptConnection()
{
  _acceptor.async_accept(_socket, [this](std::error_code ec) {
    if (!ec)
    {
      this->ReadData();
    }

    AcceptConnection();
  });
}

void TcpServer::ReadData()
{
  _socket.async_read_some(asio::buffer(_buffer, MAX_LENGTH), [this](std::error_code ec, std::size_t length) {
    if (!ec)
    {
      std::string response = this->HandleRequest(std::string(_buffer, length));
      this->WriteData(response);
    }
  });
}

void TcpServer::WriteData(std::string data)
{
  asio::async_write(_socket, asio::buffer(data), [this](std::error_code ec, std::size_t /*length*/) {
    if (!ec)
    {
      ReadData();
    }
  });
}
