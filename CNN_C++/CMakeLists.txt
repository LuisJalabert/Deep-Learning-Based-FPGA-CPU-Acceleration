cmake_minimum_required(VERSION 3.13)
project(CNN_Prj)

set(CMAKE_CXX_STANDARD 17)

add_executable(CNN_Prj main.cpp CNNFunctions.hpp data_loader.hpp)