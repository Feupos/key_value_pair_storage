#include <string>

#include <gtest/gtest.h>

#include "kvpstorage/json_storage.hpp"

static const std::string TEST_FILE_NAME{"test.json"};

TEST(JsonStorageTest, Initialize_good_weather)
{
  JsonStorage storage;
  EXPECT_TRUE(storage.Initialize(TEST_FILE_NAME));
}

TEST(JsonStorageTest, InitializeSetGetDelete_good_weater)
{
  JsonStorage storage;
  EXPECT_TRUE(storage.Initialize(TEST_FILE_NAME));
  storage.SetKeyValue("foo", "bar");
  EXPECT_EQ(storage.GetKey("foo"), "bar");
  storage.DeleteKey("foo");
  EXPECT_EQ(storage.GetKey("foo"), "");
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
