cmake_minimum_required(VERSION 2.8)

project(JsonLint)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

add_definitions(
    -std=c++11
    -fno-rtti
    -fno-exceptions
    -Wall
    -Wextra
    -Werror
)

add_subdirectory(lib/json11)
include_directories(lib/json11)

add_library(JsonLint Validator.cpp ValidatorImpl.cpp)
target_link_libraries(JsonLint json11)
include_directories(${PROJECT_SOURCE_DIR})

add_executable(json-lint main.cpp)
target_link_libraries(json-lint JsonLint)

enable_testing()
add_subdirectory(tests)

#set(CMAKE_VERBOSE_MAKEFILE TRUE)
