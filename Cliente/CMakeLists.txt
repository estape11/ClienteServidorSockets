cmake_minimum_required(VERSION 3.10)
project(ClienteServidorSockets)

set(CMAKE_CXX_STANDARD 11)

add_executable(Cliente Cliente.cpp Cliente.h main.cpp)