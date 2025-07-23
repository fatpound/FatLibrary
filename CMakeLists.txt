cmake_minimum_required(VERSION 3.30)

project(FatLibrary LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED TRUE)
set (CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_CXX_SCAN_FOR_MODULES FALSE)
set (CMAKE_CXX_MODULE_STD OFF)

add_library(FatLibrary INTERFACE)

include(_misc/FatCodex/CompileOptions.cmake)

function(fatlib_add_component COMPONENT_NAME)

    file(GLOB_RECURSE
        SRC_FILES
            CONFIGURE_DEPENDS
                "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    )

    if(SRC_FILES)

        message(STATUS "Configuring 'FatLibrary::${COMPONENT_NAME}' as a static library.")
        add_library(${COMPONENT_NAME} ${SRC_FILES})
        target_include_directories(${COMPONENT_NAME}
            PUBLIC
                $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                ${PROJECT_SOURCE_DIR}
        )
        target_link_libraries(${COMPONENT_NAME} PUBLIC FatCodex::CompileOptions)

    else()

        message(STATUS "No source files found for '${COMPONENT_NAME}'. Configuring as an INTERFACE library.")
        add_library(${COMPONENT_NAME} INTERFACE)
        target_include_directories(${COMPONENT_NAME}
            INTERFACE
                $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                ${PROJECT_SOURCE_DIR}
        )
        target_link_libraries(${COMPONENT_NAME} INTERFACE FatCodex::CompileOptions)

    endif()

    add_library(FatLibrary::${COMPONENT_NAME} ALIAS ${COMPONENT_NAME})

endfunction()

add_subdirectory(Algorithm)
add_subdirectory(Automata)
add_subdirectory(Bit)
add_subdirectory(Concurrency)
add_subdirectory(Cryptography)
add_subdirectory(DSA)
add_subdirectory(File)
add_subdirectory(Geometry)
add_subdirectory(Graph)
add_subdirectory(IO)
add_subdirectory(Math)
add_subdirectory(Memory)
add_subdirectory(Random)
add_subdirectory(Traits)
add_subdirectory(Utility)
add_subdirectory(Win32_)

target_link_libraries(FatLibrary
    INTERFACE
        FatLibrary::Algorithm
        FatLibrary::Automata
        FatLibrary::Bit
        FatLibrary::Concurrency
        FatLibrary::Cryptography
        FatLibrary::DSA
        FatLibrary::File
        FatLibrary::Geometry
        FatLibrary::Graph
        FatLibrary::IO
        FatLibrary::Math
        FatLibrary::Memory
        FatLibrary::Random
        FatLibrary::Traits
        FatLibrary::Utility
        FatLibrary::Win32_
)
