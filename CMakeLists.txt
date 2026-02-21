cmake_minimum_required(VERSION 3.28)

project(FatLibrary LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED TRUE)
set (CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_CXX_MODULE_STD OFF)

option(FATLIBRARY_ENABLE_MODULES_SUPPORT "Enable C++20 module support")

if(FATLIBRARY_ENABLE_MODULES_SUPPORT AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/FatPound.ixx")
    add_library(FatLibrary STATIC FatPound.ixx)
    message(STATUS "Adding module 'FatPound.ixx'")
    target_sources(FatLibrary
        PUBLIC
            FILE_SET CXX_MODULES FILES
                "${CMAKE_CURRENT_SOURCE_DIR}/FatPound.ixx"
    )
else()
    add_library(FatLibrary INTERFACE)
endif()

include(_misc/FatCodex/CompileOptions.cmake)

function(fatlib_add_component COMPONENT_NAME)

    set(PARENT_COMPONENT_NAME ${ARGV1})

    file(GLOB_RECURSE
        SRC_FILES
            CONFIGURE_DEPENDS
                "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    )

    if(FATLIBRARY_ENABLE_MODULES_SUPPORT)
        file(GLOB
            MOD_INTF_UNITS
                CONFIGURE_DEPENDS
                    "${CMAKE_CURRENT_SOURCE_DIR}/*.ixx"
                    "${CMAKE_CURRENT_SOURCE_DIR}/modules/*.ixx"
        )

        message(STATUS "Configuring 'FatLibrary::${COMPONENT_NAME}' as a STATIC library")

        add_library(${COMPONENT_NAME} STATIC ${MOD_INTF_UNITS} ${SRC_FILES})

        target_include_directories(${COMPONENT_NAME}
            PUBLIC
                $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                ${PROJECT_SOURCE_DIR}
        )
        
        target_sources(${COMPONENT_NAME}
            PUBLIC
                FILE_SET
                    CXX_MODULES FILES ${MOD_INTF_UNITS}
        )

        target_link_libraries(${COMPONENT_NAME} PUBLIC FatCodex::CompileOptions)

    elseif(SRC_FILES)

        message(STATUS "Configuring 'FatLibrary::${COMPONENT_NAME}' as a static library")
        add_library(${COMPONENT_NAME} STATIC ${SRC_FILES})
        target_include_directories(${COMPONENT_NAME}
            PUBLIC
                $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                ${PROJECT_SOURCE_DIR}
        )
        target_link_libraries(${COMPONENT_NAME} PUBLIC FatCodex::CompileOptions)

    else()

        message(STATUS "No source files or modules found for '${COMPONENT_NAME}' configuring as INTERFACE")
        add_library(${COMPONENT_NAME} INTERFACE)

        target_include_directories(${COMPONENT_NAME}
            INTERFACE
                $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                ${PROJECT_SOURCE_DIR}
        )

        target_link_libraries(${COMPONENT_NAME} INTERFACE FatCodex::CompileOptions)

    endif()

    add_library(FatLibrary::${COMPONENT_NAME} ALIAS ${COMPONENT_NAME})

    if(PARENT_COMPONENT_NAME)

        get_target_property(PARENT_TYPE ${PARENT_COMPONENT_NAME} TYPE)

        if(PARENT_TYPE STREQUAL "INTERFACE_LIBRARY")
            set(LINK_TYPE INTERFACE)
        else()
            set(LINK_TYPE PUBLIC)
        endif()

        message(STATUS "Linking ${PARENT_COMPONENT_NAME} to ${COMPONENT_NAME} as ${LINK_TYPE}")
        target_link_libraries(${PARENT_COMPONENT_NAME} ${LINK_TYPE} ${COMPONENT_NAME})
        
    endif()

endfunction()

add_subdirectory(Algorithm)
add_subdirectory(Automata)
add_subdirectory(Bit)
add_subdirectory(Colors)
add_subdirectory(Concurrency)
add_subdirectory(Cryptography)
add_subdirectory(DSA)
add_subdirectory(File)
add_subdirectory(Geometry)
add_subdirectory(Graph)
add_subdirectory(IO)
add_subdirectory(Math)
add_subdirectory(Memory)
add_subdirectory(Numbers)
add_subdirectory(Random)
add_subdirectory(Traits)
add_subdirectory(Utility)
add_subdirectory(Win32_)

if(FATLIBRARY_ENABLE_MODULES_SUPPORT)
    target_link_libraries(FatLibrary
        PUBLIC
            FatLibrary::Algorithm
            FatLibrary::Automata
            FatLibrary::Bit
            FatLibrary::Colors
            FatLibrary::Concurrency
            FatLibrary::Cryptography
            FatLibrary::DSA
            FatLibrary::File
            FatLibrary::Geometry
            FatLibrary::Graph
            FatLibrary::IO
            FatLibrary::Math
            FatLibrary::Memory
            FatLibrary::Numbers
            FatLibrary::Random
            FatLibrary::Traits
            FatLibrary::Utility
            FatLibrary::Win32_
    )
else()
    target_link_libraries(FatLibrary
        INTERFACE
            FatLibrary::Algorithm
            FatLibrary::Automata
            FatLibrary::Bit
            FatLibrary::Colors
            FatLibrary::Concurrency
            FatLibrary::Cryptography
            FatLibrary::DSA
            FatLibrary::File
            FatLibrary::Geometry
            FatLibrary::Graph
            FatLibrary::IO
            FatLibrary::Math
            FatLibrary::Memory
            FatLibrary::Numbers
            FatLibrary::Random
            FatLibrary::Traits
            FatLibrary::Utility
            FatLibrary::Win32_
    )
endif()
