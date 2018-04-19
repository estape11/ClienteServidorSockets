cmake_minimum_required(VERSION 3.10)
project(ClienteServidorSockets)

set(CMAKE_CXX_STANDARD 11)

add_executable(Servidor main.cpp Servidor.cpp Servidor.h)