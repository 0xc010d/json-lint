cmake_minimum_required(VERSION 2.8)

add_subdirectory(../lib/googletest/googletest lib/googletest/googletest)
include_directories(${gtest_SOURCE_DIR}/include)

include_directories(${json11_SOURCE_DIR})
include_directories(${JsonLint_SOURCE_DIR})

set(TEST_FILES
    GlobalTests.cpp
    RefTests.cpp
    AdditionalItemsTests.cpp
    AdditionalPropertiesTests.cpp
    AllOfTests.cpp
    AnyOfTests.cpp
    DependenciesTests.cpp
    EnumTests.cpp
    ItemsTests.cpp
    MaxItemsTests.cpp
    MaxLengthTests.cpp
    MaxPropertiesTests.cpp
    MaximumTests.cpp
    MinItemsTests.cpp
    MinLengthTests.cpp
    MinPropertiesTests.cpp
    MinimumTests.cpp
    MultipleOfTests.cpp
    NotTests.cpp
    OneOfTests.cpp
    PatternTests.cpp
    PatternPropertiesTests.cpp
    PropertiesTests.cpp
    RequiredTests.cpp
    TypeTests.cpp
    UniqueItemsTests.cpp
    )

#foreach (FILE ${TEST_FILES})
#  string(REGEX REPLACE "^(.+)Tests\\.cpp$" "validator-tests-\\1" TEST_NAME ${FILE})
#  add_executable(${TEST_NAME} main.cpp ${FILE})
#  target_link_libraries(${TEST_NAME} gtest_main JsonLint)
#  add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
#endforeach ()

add_executable(validator-tests main.cpp ${TEST_FILES})
target_link_libraries(validator-tests gtest_main JsonLint)
add_test(NAME validator-tests COMMAND validator-tests)
