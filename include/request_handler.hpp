#pragma once

#include <memory>
#include <string>

#include "storage_interface.hpp"

class RequestHandler
{
 public:
  RequestHandler(std::shared_ptr<StorageInterface> storage);
  ~RequestHandler() = default;
  std::string HandleRequest(std::string request);
  //void ReplyRequest(std::string reply);

 private:
  std::shared_ptr<StorageInterface> _storage;
};
