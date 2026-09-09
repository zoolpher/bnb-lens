cmake_minimum_required(VERSION 3.10)
project(bnb_lens VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -O2)
endif()

# We are temporarily disabling Boost and OpenSSL until we start the Networking phase
# find_package(Boost REQUIRED COMPONENTS system thread)
# find_package(OpenSSL REQUIRED)
# find_package(Threads REQUIRED)
# find_package(ZLIB REQUIRED)

include_directories(include)

add_executable(binance_capture 
    src/main.cpp 
    src/OrderBook.cpp 
    src/CSVWriter.cpp
)

# target_link_libraries(binance_capture
#     PRIVATE
#     Boost::system
#     Boost::thread
#     OpenSSL::SSL
#     OpenSSL::Crypto
#     Threads::Threads
#     ZLIB::ZLIB
# )
