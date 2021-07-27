cmake_minimum_required(VERSION 3.19)
project(sharedQueue)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)
file(GLOB INCLUDES
        include/queue/sharedQueue.hpp
        )
add_executable(sharedQueue main.cpp include/queue/sharedQueue.hpp ${INCLUDES})
target_link_libraries(sharedQueue
        pthread)
