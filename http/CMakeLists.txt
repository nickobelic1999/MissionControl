cmake_minimum_required(VERSION 3.20)
project(MissionControl_HTTP)

include_directories(../extern_libs/curlpp/include)
include_directories(../toolbox)

add_library(MissionControl_HTTP httpEngineClient.cpp httpEngineClient.hpp)

target_link_libraries(MissionControl_HTTP curlpp MissionControl_Utils)
