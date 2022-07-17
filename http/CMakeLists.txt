cmake_minimum_required(VERSION 3.20)
project(MissionControl_HTTP)


add_library(MissionControl_HTTP RequestHTTP.cpp RequestHTTP.hpp)
