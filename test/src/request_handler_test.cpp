#include <string>
#include <memory>

#include <gtest/gtest.h>

#include "json_storage.hpp"
#include "request_handler.hpp"

static const std::string TEST_FILE_NAME{"test.json"};



class RequestHandlerTest : public ::testing::Test {
 protected:
  void SetUp() override {
     _storage->Initialize(TEST_FILE_NAME);
  }
  public:
    // Ideally storage class should be mocked to isolate the unit tests
    std::shared_ptr<JsonStorage> _storage = std::make_shared<JsonStorage>();
};

TEST_F(RequestHandlerTest, HandleSetGetDelete_good_weather)
{
    RequestHandler request_handler(_storage);
    EXPECT_EQ(request_handler.HandleRequest("SET foo bar"), "OK");
    EXPECT_EQ(request_handler.HandleRequest("GET foo"), "bar");
    EXPECT_EQ(request_handler.HandleRequest("DELETE foo"), "OK");
    EXPECT_EQ(request_handler.HandleRequest("GET foo"), "");
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
