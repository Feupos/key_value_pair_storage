[![Actions Status](https://github.com/Feupos/key_value_pair_storage/workflows/Ubuntu/badge.svg)](https://github.com/Feupos/key_value_pair_storage/actions)
[![codecov](https://codecov.io/gh/Feupos/key_value_pair_storage/branch/master/graph/badge.svg)](https://codecov.io/gh/Feupos/key_value_pair_storage)
[![GitHub release (latest by date)](https://img.shields.io/github/v/release/Feupos/key_value_pair_storage)](https://github.com/Feupos/key_value_pair_storage/releases)

# Key Value Pair Storage

Simple application to allow storage of key value pairs.

Template for project structure is generated with base from https://github.com/filipdutescu/modern-cpp-template

### Prerequisites

To use the project you need the following tools:

* **CMake v3.15+** - found at [https://cmake.org/](https://cmake.org/)

* **C++ Compiler** - needs to support at least the **C++17** standard, i.e. *MSVC*,
*GCC*, *Clang*

You also need to install the dependencies for gtest, nhloman json and boost. This can be done in Ubuntu with the following commands:

```bash
wget -c 'http://sourceforge.net/projects/boost/files/boost/1.80.0/boost_1_80_0.tar.bz2/download'
tar xf download
cd boost_1_80_0
./bootstrap.sh
sudo ./b2 install
cd ..
git clone https://github.com/google/googletest.git --branch release-1.10.0
cd googletest
cmake -Bbuild -DCMAKE_INSTALL_PREFIX="$HOME/.local" -Dgtest_force_shared_crt=1
cmake --build build --config Release
cmake --build build --target install --config Release
git clone https://github.com/nlohmann/json.git --branch v3.11.2
cd json
cmake -Bbuild -DCMAKE_INSTALL_PREFIX="$HOME/.local"
cmake --build build --config Release
cmake --build build --target install --config Release
```

## Building the project

To build the project, all you need to do is run a similar **CMake** routine
to the the one below:

```bash
mkdir build/ && cd build/
cmake ..
cmake --build . --target install
```

## Generating the documentation

In order to generate documentation for the project, you need to configure the build
to use Doxygen. This is easily done, by modifying the workflow shown above as follows:

```bash
mkdir build/ && cd build/
cmake .. -DKVPStorage_ENABLE_DOXYGEN=1 -DCMAKE_INSTALL_PREFIX=/absolute/path/to/custom/install/directory
cmake --build . --target doxygen-docs
```

> ***Note:*** *This will generate a `docs/` directory in the **project's root directory**.*

## Running the tests

[Google Test](https://github.com/google/googletest/) is used
for unit testing. Unit testing can be disabled in the options, by setting the
`ENABLE_UNIT_TESTING` (from
[cmake/StandardSettings.cmake](cmake/StandardSettings.cmake)) to be false. To run
the tests, simply use CTest, from the build directory, passing the desire
configuration for which to run tests for. An example of this procedure is:

```bash
cd build          # if not in the build directory already
ctest -C Release  # or `ctest -C Debug` or any other configuration you wish to test

# you can also run tests with the `-VV` flag for a more verbose output (i.e.
#GoogleTest output as well)
```

## Authors

* **Felipe dos Santos Neves** - [@feupos](https://github.com/Feupos)

## License

This project is licensed under the [Unlicense](https://unlicense.org/) - see the
[LICENSE](LICENSE) file for details
