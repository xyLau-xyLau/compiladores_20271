cmake_minimum_required(VERSION 3.16)
project(regex_to_nfa LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(regex_to_nfa
    ./src/main.cpp)
