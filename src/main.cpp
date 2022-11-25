#include <getopt.h>

#include <iostream>
#include <memory>

#include "asio.hpp"
#include "json_storage.hpp"
#include "tcp_server.hpp"
#include "request_handler.hpp"

int main(int argc, char** argv)
{
  int is_server{ 0 };
  short unsigned int tcp_port{ 48620 };
  std::string file_name{ "data.json" };
  static const char short_options[] = "p:f:";
  static const option long_options[] = { { "tcp", no_argument, &is_server, 1 },
                                         { "port", required_argument, 0, 'p' },
                                         { "file", required_argument, 0, 'f' },
                                         { 0, 0, 0, 0 } };

  static const char help_text[] =
      "--tcp : Run as a TCP server instead of console\n"
      "--port <p> : Set TPC port to listen (default 48620)\n"
      "--file <file_name> : Spefify file name to store the data (default data.json)";

  int opt;
  while ((opt = getopt_long(argc, argv, short_options, long_options, nullptr)) != -1)
  {
    switch (opt)
    {
      case 0:
      {
        break;
      }
      case 'p':
      {
        tcp_port = static_cast<short unsigned int>(std::stoi(optarg));
        break;
      }
      case 'f':
      {
        file_name = std::string(optarg);
        break;
      }
      case 'h':  // -h or --help
      case '?':  // Unrecognized option
      default:
      {
        std::cout << help_text;
        break;
      }
    }
  }

  std::shared_ptr<StorageInterface> storage = std::make_shared<JsonStorage>();
  storage->Initialize(file_name);

  if (is_server != 0)
  {
    asio::io_context io_context;
    TcpServer server(io_context, storage, tcp_port);

    io_context.run();
  }
  else
  {
    RequestHandler handler(storage);
    std::string input;
    std::string response;
    while (true)
    {
      std::cout << "> ";
      std::getline(std::cin, input);
      response = handler.HandleRequest(input);
      std::cout << response << "\n";
    }
  }

  return 0;
}