cmake_minimum_required(VERSION 3.24)
project(2hc2022)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(2hc2022
        src/main_a.cpp src/utils.h src/graph.h src/worker.h src/job.h)
