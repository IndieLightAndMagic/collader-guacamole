#CMAKE TO MAKE A STATIC LIBRARY
#HEADER
cmake_minimum_required(VERSION 3.9.0 FATAL_ERROR)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(TARGET_NAME Collader)
project(${TARGET_NAME})
set(CMAKE_CXX_STANDARD 17)

#DIRECTORIES
get_filename_component(ROOT_DIR "." ABSOLUTE)
message(STATUS "SYSTEM NAME: ${CMAKE_SYSTEM_NAME}")
message(STATUS "ROOT_DIR: ${ROOT_DIR}")
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "-----------------------------")

#GLM
set(GLM_DIR "${ROOT_DIR}/../GLM")


add_executable(${TARGET_NAME} collader.h collader.cpp tinyxml2/tinyxml2.cpp tinyxml2/tinyxml2.h)
target_include_directories(${TARGET_NAME} PUBLIC ${GLM_DIR})
