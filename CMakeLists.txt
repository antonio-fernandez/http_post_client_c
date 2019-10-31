cmake_minimum_required(VERSION 3.5)
project(http_client_c C)

set(CMAKE_C_STANDARD 11)

add_executable(http_client_c main.c)

target_link_libraries(http_client_c curl)