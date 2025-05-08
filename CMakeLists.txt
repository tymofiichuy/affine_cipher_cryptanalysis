cmake_minimum_required(VERSION 3.10)
project(affine_cipher)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(MAIN_DIR ${CMAKE_SOURCE_DIR}/main)

set(SOURCES
    ${SOURCE_DIR}/modular_arithmetic.cpp 
    ${SOURCE_DIR}/affine_cipher.cpp
)

include_directories(${SOURCE_DIR})

# add_executable(key_recovery ${MAIN_DIR}/key_recovery_driver.cpp ${SOURCES})