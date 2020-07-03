cmake_minimum_required(VERSION 3.15)
project(ARBAC)

set(CMAKE_CXX_STANDARD 14)

add_executable(ARBAC main.cpp Models/Policy.cpp Models/CA.cpp Models/CR.cpp Models/UR.cpp Controls/Parser.cpp Controls/Utility.cpp)