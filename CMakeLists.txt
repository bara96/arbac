cmake_minimum_required(VERSION 3.15)
project(ARBAC)

set(CMAKE_CXX_STANDARD 14)

add_executable(ARBAC main.cpp Controls/Parser.cpp Models/CA/CA.cpp Models/CA/CA.h Controls/PolicyAnalyzer.cpp Models/UR/UR.cpp Models/UR/UR.h Models/CR/CR.cpp Models/CR/CR.h Models/Policy/Policy.cpp Models/Policy/Policy.h Controls/Utility/Utility.cpp Controls/Utility/Utility.h Models/Rule/Rule.h Controls/Cache.cpp)