cmake_minimum_required(VERSION 3.10)

project(ThreadPool)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_library(ThreadPool
    src/ThreadPool.cpp
)

add_executable(example
    examples/main.cpp
)

target_link_libraries(example ThreadPool)

add_executable(benchmark
    benchmark/benchmark.cpp
)

target_link_libraries(benchmark ThreadPool)