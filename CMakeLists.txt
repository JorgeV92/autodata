cmake_minimum_required(VERSION 3.20)
project(autodata VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(AUTODATA_BUILD_TESTS "Build C++ unit tests" ON)

add_library(autodata_core SHARED
    src/range_dataset.cpp
    src/vector_dataset.cpp
    src/shuffle_dataset.cpp
    src/slice_dataset.cpp
    src/batch_dataset.cpp
)

add_library(autodata::core ALIAS autodata_core)

target_include_directories(autodata_core
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

if(MSVC)
    target_compile_definitions(autodata_core PRIVATE AUTODATA_EXPORTS)
else()
    target_compile_options(autodata_core PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(autodata_core PROPERTIES
    OUTPUT_NAME "autodata_core"
    POSITION_INDEPENDENT_CODE ON
)


include(CTest)
if(BUILD_TESTING AND AUTODATA_BUILD_TESTS)
    add_executable(autodata_cpp_tests
        tests/cpp/test_main.cpp
    )
    target_link_libraries(autodata_cpp_tests PRIVATE autodata::core)
    add_test(NAME autodata_cpp_tests COMMAND autodata_cpp_tests)
endif()
