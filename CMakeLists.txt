cmake_minimum_required(VERSION 3.30)

project(FatLibrary LANGUAGES CXX)

add_library(FatLibrary INTERFACE)

target_include_directories(FatLibrary
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_compile_features(FatLibrary INTERFACE cxx_std_20)
