#include "storage_interface.hpp"

class JsonStorage : public StorageInterface
{
 public:
  bool Initialize(const std::string& file_name);
  bool SetKeyValue(const std::string& key, const std::string& value);
  bool DeleteKey(const std::string& key);
  std::string GetKey(const std::string& key);
};