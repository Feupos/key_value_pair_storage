#pragma once

#include <gmock/gmock.h>

#include <boost/asio.hpp>
#include <functional>

using boost::asio::ip::tcp;

typedef std::function<void(const boost::system::error_code&, std::size_t)> async_handler_socket;
typedef std::function<void(const boost::system::error_code&)> async_handler_acceptor;

class MockSocket
{
 public:
  MockSocket(){};
  MOCK_METHOD(void, async_read_some, (boost::asio::mutable_buffer, async_handler_socket), (const));
  MOCK_METHOD(void, async_write_some, (boost::asio::mutable_buffer, async_handler_socket), (const));
  MOCK_METHOD(void, close, (), (const));
};

class MockAcceptor
{
 public:
  MockAcceptor(){};
  MOCK_METHOD(void, async_accept, (MockSocket&, async_handler_acceptor), (const));
  MOCK_METHOD(void, open, (tcp::endpoint::protocol_type), (const));
  MOCK_METHOD(void, set_option, (boost::asio::socket_base::reuse_address), (const));
  MOCK_METHOD(void, bind, (tcp::endpoint&), (const));
  MOCK_METHOD(void, listen, (), (const));
  MOCK_METHOD(void, close, (), (const));
};
