cmake_minimum_required(VERSION 3.16)
project(sharedQueue)

set(CMAKE_CXX_STANDARD 17)
set (THIRD_PARTY_LIBS third_party/lib)
set (THIRD_PARTY_INCLUDE third_party/include)
include_directories(third_party/include
        include/)

file(GLOB INCLUDES
        include/queue/sharedQueue.hpp
        )

add_executable(${PROJECT_NAME} main.cpp include/queue/sharedQueue.hpp ${INCLUDES})
target_link_libraries(${PROJECT_NAME}
        pthread)
add_subdirectory(tests)