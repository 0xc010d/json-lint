add_subdirectory(../lib/googletest/googletest lib/googletest/googletest)
include_directories(${gtest_SOURCE_DIR}/include)

include_directories(${json11_SOURCE_DIR})
include_directories(${JsonLint_SOURCE_DIR})

set(SRC main.cpp ValidatorTests.cpp)

add_executable(validator-tests ${SRC})
target_link_libraries(validator-tests gtest_main JsonLint)
add_test(NAME validator-tests COMMAND validator-tests)
