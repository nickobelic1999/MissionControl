cmake_minimum_required(VERSION 3.20)
project(MissionControl_Utils)

add_library(MissionControl_Utils    utils.cpp utils.hpp
                                    credentials.cpp credentials.hpp)