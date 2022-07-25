cmake_minimum_required(VERSION 3.20)
project(MissionControl)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(./extern_libs/curlpp)
include_directories(./extern_libs/curlpp/include)

add_subdirectory(./extern_libs/pugixml)
include_directories(./extern_libs/pugixml/src/)

add_subdirectory(./http)
include_directories(./http)

add_subdirectory(./toolbox)
include_directories(./toolbox)

add_subdirectory(./s3)
include_directories(./s3)
add_executable(MissionControl main.cpp)

target_link_libraries(MissionControl MissionControl_S3)