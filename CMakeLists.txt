cmake_minimum_required(VERSION 3.15)
project(ARBAC)

set(CMAKE_CXX_STANDARD 14)

add_executable(ARBAC main.cpp Models/Policy/Policy.cpp Models/CA/CA.cpp Models/CR/CR.cpp Models/UR/UR.cpp)