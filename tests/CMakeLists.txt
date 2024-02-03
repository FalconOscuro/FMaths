enable_testing()

find_package(Catch2 REQUIRED)

add_executable(Vector3 Vector3.cpp)

target_link_libraries(Vector3
    PRIVATE Catch2::Catch2WithMain
    PRIVATE ${PROJECT_NAME}
)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(Vector3
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)