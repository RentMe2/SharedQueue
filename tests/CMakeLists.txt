cmake_minimum_required(VERSION 3.16)
project(SHARED_QUEUE_TEST)

set(CMAKE_CXX_STANDARD 17 )
set (CMAKE_CXX_FLAGS "-std=c++17 -fprofile-arcs -ftest-coverage --coverage")
file(GLOB TEST_CPP
        sharedQueue/include/queue/sharedQueue.cpp
        )
file (GLOB TEST_INCLUDES
        ${THIRD_PARTY_INCLUDES}/include/Catch.hpp
        )
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} test.cpp  ${TEST_CPP} ${TEST_INCLUDES})

target_link_libraries(${PROJECT_NAME}
        pthread
        gcov)
