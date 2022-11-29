#include "kvpstorage/tcp_server.hpp"

#include <gtest/gtest.h>

#include <boost/asio.hpp>
#include <functional>
#include <memory>

#include "kvpstorage/json_storage.hpp"
#include "kvpstorage/request_handler.hpp"
#include "mocks.hpp"

using testing::_;

static const std::string TEST_FILE_NAME{ "test.json" };

class TcpServerTest : public ::testing::Test
{
 protected:
  void SetUp() override
  {
    _storage->Initialize(TEST_FILE_NAME);
  }

 public:
  // Ideally storage class should be mocked to isolate the unit tests
  std::shared_ptr<StorageInterface> _storage = std::make_shared<JsonStorage>();
};

TEST_F(TcpServerTest, TcpServerRead)
{
  boost::asio::io_context io_context;
  MockAcceptor acceptor;
  MockSocket socket;

  EXPECT_CALL(socket, async_read_some(_, _))
      .WillOnce(testing::Invoke([](boost::asio::mutable_buffer data, async_handler_socket func) {
        strncpy((char *)data.data(), "GET test\0", 9);
        func(boost::system::error_code(), 8);
      }))
      .WillOnce(testing::Invoke([](boost::asio::mutable_buffer data, async_handler_socket func) {
        func(boost::system::errc::make_error_code(boost::system::errc::connection_aborted), 0);
      }));

  EXPECT_CALL(acceptor, async_accept(_, _))
      .WillOnce(testing::Invoke([](MockSocket &socket, async_handler_acceptor func) { func(boost::system::error_code()); }))
      .WillOnce(testing::Invoke([](MockSocket &socket, async_handler_acceptor func) {}));

  // Expected reply based on mock data
  auto expected_response = boost::asio::buffer("OK", 3);
  EXPECT_CALL(socket, async_write_some(_, _))
      .WillOnce(testing::Invoke(
          [](boost::asio::mutable_buffer data, async_handler_socket func) { func(boost::system::error_code(), 0); }));

  // On creations will accept mock connection and read mock data
  TcpServer<MockAcceptor, MockSocket> tcp_server(acceptor, socket, this->_storage);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
