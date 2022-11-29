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
};

class MockAcceptor
{
 public:
  MockAcceptor(){};
  MOCK_METHOD(void, async_accept, (MockSocket&, async_handler_acceptor), (const));
};
