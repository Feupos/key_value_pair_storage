#include <memory>
#include <vector>
#include <string>
#include <iostream>

#include "kvpstorage/request_handler.hpp"

static const char REQUEST_DELIMITERS[] = {' ', '\n', '\r'};

RequestHandler::RequestHandler(std::shared_ptr<StorageInterface> storage): _storage{storage}
{
}

std::string RequestHandler::HandleRequest(std::string request)
{
    size_t pos = 0;
    std::vector<std::string> query;
    std::string response = "";

    // Parse all command parameters
    while ((pos = request.find_first_of(REQUEST_DELIMITERS)) != std::string::npos)
    {
        query.push_back(request.substr(0, pos));
        request.erase(0, pos + 1);
    }
    // Last parameter from request if without end delimiter
    if(request.size() > 0)
    {
        query.push_back(request);
    }

    if(query.size() > 0)
    {
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
    }

    return response;
}
