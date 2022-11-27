#include <fstream>
#include <iostream>

#include "kvpstorage/json_storage.hpp"

bool JsonStorage::Initialize(const std::string& file_name)
{
  bool ret{true};

  // Initialize storage by reading from json file
  try
  {
    this->_file_name = file_name;
    std::fstream file(this->_file_name, std::ios::in | std::ios::out);
    try
    {
      this->_data = json::parse(file);
      file.close();
    }
    catch(const json::parse_error& e)
    {
      // In case of parse error save empty data to file
      this->SaveDataToFile();
    }  
    
  }
  catch(const std::exception& e)
  {
    ret = false;
  }

  return ret;
}

bool JsonStorage::SetKeyValue(const std::string& key, const std::string& value)
{
  bool ret{true};

  try
  {
    this->_data[key] = value;
    this->SaveDataToFile();
  }
  catch(const std::exception& e)
  {
    ret = false;
  }
  
  return ret;
}

bool JsonStorage::DeleteKey(const std::string& key)
{
  bool ret{true};

  try
  {
    auto pos = this->_data.find(key);
    if (pos != this->_data.end())
    {
      this->_data.erase(pos);
      this->SaveDataToFile();
    }
  }
  catch(const std::exception& e)
  {
    ret = false;
  }
  
  return ret;
}

std::string JsonStorage::GetKey(const std::string& key)
{
  std::string ret;
  try
  {
    ret = this->_data[key];
  }
  catch(const std::exception& e)
  {
    // Return empty string in case key is not found
    ret = "";
  }
  
  return ret;
}

bool JsonStorage::SaveDataToFile()
{
  bool ret{true};

  try
  {
    std::ofstream file(this->_file_name);
    file << this->_data.dump();
    file.close();
  }
  catch(const std::exception& e)
  {
    ret = false;
  }
  
  return ret;
}