cmake_minimum_required(VERSION 3.21)
project(EngineCore)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE CPP_SOURCES RELATIVE ${CMAKE_SOURCE_DIR}
        "Application/*.cpp"
        "Core/*.cpp")

add_executable(EngineCore ${CPP_SOURCES})
