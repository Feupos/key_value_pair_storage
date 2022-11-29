#include "kvpstorage/request_handler.hpp"

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

static const char REQUEST_DELIMITER = ' ';

void SanitizeInput(std::string &stringValue)
{
  // Add backslashes
  for (auto i = stringValue.begin();;)
  {
    auto const pos = std::find_if(i, stringValue.end(), [](char const c) { return '\\' == c || '\'' == c || '"' == c; });
    if (pos == stringValue.end())
    {
      break;
    }
    i = std::next(stringValue.insert(pos, '\\'), 2);
  }

  // Removes others
  stringValue.erase(
      std::remove_if(
          stringValue.begin(),
          stringValue.end(),
          [](char const c) { return '\n' == c || '\r' == c || '\0' == c || '\x1A' == c; }),
      stringValue.end());
}

RequestHandler::RequestHandler(std::shared_ptr<StorageInterface> storage) : _storage{ storage }
{
}

std::string RequestHandler::HandleRequest(std::string request)
{
  size_t pos = 0;
  std::vector<std::string> query;
  std::string response{};

  // Remove unwanted characters from input
  SanitizeInput(request);

  // Parse all command parameters
  while ((pos = request.find(' ')) != std::string::npos)
  {
    query.push_back(request.substr(0, pos));
    request.erase(0, pos + 1);
  }
  // Last parameter from request if without end delimiter
  if (!request.empty())
  {
    query.push_back(request);
  }

  if (!query.empty())
  {
    if (query[0] == "GET")
    {
      if (query.size() == 2)
      {
        response = _storage->GetKey(query[1]);
      }
      else
      {
        response = "Invalid arguments";
      }
    }
    else if (query[0] == "SET")
    {
      if (query.size() == 3)
      {
        _storage->SetKeyValue(query[1], query[2]);
        response = "OK";
      }
      else
      {
        response = "Invalid arguments";
      }
    }
    else if (query[0] == "DELETE")
    {
      if (query.size() == 2)
      {
        _storage->DeleteKey(query[1]);
        response = "OK";
      }
      else
      {
        response = "Invalid arguments";
      }
    }
    else
    {
<<<<<<< HEAD
        if(query[0] == "GET")
        {
            if(query.size() >=  2)
            {
                response = _storage->GetKey(query[1]);
            }
            else
            {
                response = "Invalid arguments";
                for(auto arg: query)
                {
                    std::cout << arg << std::endl;
                }
            }
        }
        else if(query[0] == "SET")
        {
            if(query.size() ==  3)
            {
                _storage->SetKeyValue(query[1], query[2]);
                response = "OK";
            }
            else
            {
                response = "Invalid arguments";
                for(auto arg: query)
                {
                    std::cout << arg << std::endl;
                }
            }
        }
        else if(query[0] == "DELETE")
        {
            if(query.size() ==  2)
            {
                _storage->DeleteKey(query[1]);
                response = "OK";
            }
            else
            {
                response = "Invalid arguments";
                for(auto arg: query)
                {
                    std::cout << arg << std::endl;
                }
            }
        }
        else
        {
            response = "Unknown Command";
        }
=======
      response = "Unknown Command";
>>>>>>> 9d642268ced4b81d951c857e6775b22211b3d44c
    }
  }

  return response;
}
