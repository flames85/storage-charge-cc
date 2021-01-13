cmake_minimum_required(VERSION 3.14)

project(storage_charge C CXX)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Warnings
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif()

# Enable Testing
include(CTest)
enable_testing()

# Target: storage_charge
file(GLOB all_srcs CMAKE_CONFIGURE_DEPENDS
    src/*.cc
    src/*.c
)

add_library(storage_charge ${all_srcs})

target_include_directories(storage_charge 
  PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/include
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
)

# Target: storage_charge_test

file(GLOB all_tests CMAKE_CONFIGURE_DEPENDS
    test/*.cc
    test/*.c
)

add_executable(storage_charge_test ${all_tests})

target_include_directories(storage_charge_test 
  PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/test
)

target_link_libraries(storage_charge_test 
  PRIVATE
    storage_charge 
    gtest 
    gtest_main
)

add_test(NAME storage_charge_test COMMAND storage_charge_test)