cmake_minimum_required(VERSION 3.10)
project(bnb_lens VERSION 1.0.0 LANGUAGES CXX)

# Enforce C++17 as required by the project specifications
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add strict compiler flags for code quality and optimization (-O2 for performance)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -O2)
endif()

# Find necessary dependencies
find_package(Boost REQUIRED COMPONENTS system thread)
find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)
find_package(ZLIB REQUIRED)

# Specify where our header files will live
include_directories(include)

# Define our main executable (we will create main.cpp next)
add_executable(binance_capture src/main.cpp)

# Link the dependencies to our executable
target_link_libraries(
    binance_capture
    PRIVATE
    Boost::system
    Boost::thread
    OpenSSL::SSL
    OpenSSL::Crypto
    Threads::Threads
    ZLIB::ZLIB
)
