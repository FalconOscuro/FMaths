enable_testing()

find_package(Catch2 REQUIRED)

set(TEST_LIBS
    Catch2::Catch2WithMain
    ${PROJECT_NAME}
)

add_executable(Vector3 Vector3.cpp)

target_link_libraries(Vector3
    PRIVATE ${TEST_LIBS}
)

add_executable(Matrix Matrix.cpp)

target_link_libraries(Matrix
    PRIVATE ${TEST_LIBS}
)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(Vector3
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)