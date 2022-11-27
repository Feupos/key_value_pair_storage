#pragma once

#include <boost/asio.hpp>
#include <memory>

#include "kvpstorage/request_handler.hpp"
#include "kvpstorage/storage_interface.hpp"

using boost::asio::ip::tcp;

static constexpr int MAX_LENGTH = 1024;

class TcpServer : RequestHandler
{
 public:
  TcpServer(boost::asio::io_context& io_context, std::shared_ptr<StorageInterface> storage, short unsigned int port);
 private:
  void AcceptConnection();
  void ReadData();
  void WriteData(std::string data);

  char _buffer[MAX_LENGTH];
  tcp::acceptor _acceptor;
  tcp::socket _socket;
};