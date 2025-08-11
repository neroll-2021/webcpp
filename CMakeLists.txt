cmake_minimum_required(VERSION 3.28)

project(webcpp VERSION 0.1.0 LANGUAGES CXX)

# Set default build type to release.
set(DEFAULT_BUILD_TYPE "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()

set(EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(webcpp src/main.cpp)
target_include_directories(webcpp PUBLIC include)

if(WEBCPP_NO_EXCEPTION)
    message(STATUS "Exceptions are disabled.")
    target_compile_definitions(webcpp PUBLIC WEBCPP_NO_EXCEPTION)
    if(MSVC)
        target_compile_options(webcpp PRIVATE /EHsc)
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        target_compile_options(webcpp PRIVATE -fno-exceptions)
        if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            target_link_libraries(webcpp PUBLIC stdc++exp)
        endif()
    else()
        message(WARNING "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}")
    endif()
endif()