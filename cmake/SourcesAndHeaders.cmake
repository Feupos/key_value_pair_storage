set(sources
    src/json_storage.cpp
)

set(exe_sources
		src/main.cpp
		${sources}
)

set(headers
    include/storage_interface.hpp
    include/json_storage.hpp
)

set(test_sources
  src/json_storage_test.cpp
)
