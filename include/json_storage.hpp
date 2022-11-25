#pragma once

#include <nlohmann/json.hpp>
#include <string>

#include "storage_interface.hpp"

using json = nlohmann::json;

/* 
This is a basic storage system using json files used to implement
an MVP version of the application, it has slow performance and does
not allow concurrent access to the storage 
*/
class JsonStorage : public StorageInterface
{
 public:
  bool Initialize(const std::string& file_name);
  bool SetKeyValue(const std::string& key, const std::string& value);
  bool DeleteKey(const std::string& key);
  std::string GetKey(const std::string& key);
  bool SaveDataToFile();

 private:
  std::string _file_name;
  json _data;
};