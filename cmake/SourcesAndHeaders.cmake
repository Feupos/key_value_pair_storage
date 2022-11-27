set(sources
    src/json_storage.cpp
    src/request_handler.cpp
    src/tcp_server.cpp
)

set(exe_sources
		src/main.cpp
		${sources}
)

set(headers
    include/kvpstorage/tcp_server.hpp
    include/kvpstorage/request_handler.hpp
    include/kvpstorage/storage_interface.hpp
    include/kvpstorage/json_storage.hpp
)

set(test_sources
    src/json_storage_test.cpp
    src/request_handler_test.cpp
    src/tcp_server_test.cpp
)
