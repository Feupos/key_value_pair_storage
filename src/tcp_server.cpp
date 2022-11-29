#include "kvpstorage/tcp_server.hpp"

// Explicit instantiation of template
template class TcpServer<tcp::acceptor, tcp::socket>;