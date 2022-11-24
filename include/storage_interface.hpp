#include <string>

class StorageInterface
{
 public:
  virtual bool SetKeyValue(const std::string& key, const std::string& value) = 0;
  virtual bool DeleteKey(const std::string& key) = 0;
  virtual std::string GetKey(const std::string& key) = 0;
};
