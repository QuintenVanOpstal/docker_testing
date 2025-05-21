cmake_minimum_required(VERSION 3.10)
project(test_service)

# Set C++ standard (e.g., C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Boost
find_package(Boost REQUIRED COMPONENTS system)

# Include websocketpp (header-only library)
include_directories(/usr/include/websocketpp)

# Create executable from src/test.cpp
add_executable(test_service src/test.cpp)
target_link_libraries(test_service PRIVATE Boost::system pthread)
