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

  std::string mock_request = "SET test value\r\n\0";
  EXPECT_CALL(socket, async_read_some(_, _))
      .WillOnce(testing::Invoke([&](boost::asio::mutable_buffer data, async_handler_socket func) {
        strncpy(static_cast<char*>(data.data()), mock_request.c_str(), mock_request.size());
        func(boost::system::error_code(), mock_request.size());
      }))
      .WillOnce(testing::Invoke([](boost::asio::mutable_buffer, async_handler_socket func) {
        func(boost::system::errc::make_error_code(boost::system::errc::connection_aborted), 0);
      }));

  EXPECT_CALL(acceptor, async_accept(_, _))
      .WillOnce(testing::Invoke([](MockSocket&, async_handler_acceptor func) { func(boost::system::error_code()); }))
      .WillOnce(testing::Invoke([](MockSocket&, async_handler_acceptor) {}));

  // Expected reply based on mock data
  std::string actual_response;
  EXPECT_CALL(socket, async_write_some(_, _))
      .WillOnce(testing::Invoke(
          [&](boost::asio::mutable_buffer data, async_handler_socket func) { 
            actual_response = std::string(static_cast<char*>(data.data()), data.size());
            func(boost::system::error_code(), 0); }));

  // On creations will accept mock connection and read mock data
  TcpServer<MockAcceptor, MockSocket> tcp_server(acceptor, socket, this->_storage, 1234);

  EXPECT_EQ(actual_response, "OK");
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
