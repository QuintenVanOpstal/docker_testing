cmake_minimum_required(VERSION 3.10)
project(WebSocketServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Boost
find_package(Boost REQUIRED COMPONENTS system)

# Include websocketpp (header-only library)
include_directories(/usr/include/websocketpp)

add_executable(test_reciever src/test.cpp)

# Link Boost libraries
target_link_libraries(test_reciever PRIVATE Boost::system)

