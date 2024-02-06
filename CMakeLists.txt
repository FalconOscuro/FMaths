cmake_minimum_required(VERSION 3.22)

project(
    Falcon-Maths
    VERSION 0.2.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Get required packages
message(STATUS "Retrieving packages")

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/FMaths)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PUBLIC
    ${SRC_DIR}/Vector2.cpp
    ${SRC_DIR}/Vector3.cpp
    ${SRC_DIR}/Vector4.cpp
    ${SRC_DIR}/Matrix4x4.cpp
    ${SRC_DIR}/Quaternion.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Tests
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message(STATUS "Testing enabled for ${CMAKE_PROJECT_NAME}")
    enable_testing()
    add_subdirectory(tests)
endif()