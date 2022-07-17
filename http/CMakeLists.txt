cmake_minimum_required(VERSION 3.20)
project(MissionControl_HTTP)

include_directories(./extern_libs/curlpp/include/curlpp)

add_library(MissionControl_HTTP RequestHTTP.cpp RequestHTTP.hpp)

target_link_libraries(MissionControl_HTTP curlpp)
