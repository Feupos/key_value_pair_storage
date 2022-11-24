#include <iostream>

#include "json_storage.hpp"


int main(int argc, char** argv)
{
    if(argc != 2)
    {
        std::cout << "You must run with json_storage_server [storage_file_name.json]" << std::endl;
    }
    else
    {
        std::cout << "Initializing Key Value Pair Storage on " << argv[1] << std::endl;
    }
    JsonStorage storage;
    storage.Initialize(argv[0]);
}