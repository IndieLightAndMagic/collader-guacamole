#CMAKE TO MAKE A STATIC LIBRARY
#HEADER
cmake_minimum_required(VERSION 3.9.0 FATAL_ERROR)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(TARGET_NAME gltest)
project(${TARGET_NAME})
set(CMAKE_CXX_STANDARD 17)

#DIRECTORIES
get_filename_component(ROOT_DIR "." ABSOLUTE)
message(STATUS "SYSTEM NAME: ${CMAKE_SYSTEM_NAME}")
message(STATUS "ROOT_DIR: ${ROOT_DIR}")
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "-----------------------------")

#GTECH directory 
#Installation directory 
get_filename_component(GTECH_DIR $ENV{GTECH_ROOT} ABSOLUTE)
set(GTECH_DIR_LIB ${GTECH_DIR}/3rd/lib)
set(GTECH_DIR_INC ${GTECH_DIR}/3rd/include)


#GLM
set(GLM_INC_DIR ${GTECH_DIR}/GLM)

#COLLADER
set(COLLADER_INC_DIR ${GTECH_DIR_INC}/collader)

#SDL2 
set(SDL2_INC_DIR ${GTECH_DIR}/SDL/include) 

add_executable(${TARGET_NAME}  

    gltest.cpp
    
)

#========= INCLUDE ==============#

target_include_directories(${TARGET_NAME} PUBLIC ${GLM_INC_DIR})
target_include_directories(${TARGET_NAME} PUBLIC ${COLLADER_INC_DIR})
target_include_directories(${TARGET_NAME} PUBLIC ${SDL2_INC_DIR})
#========== LINK ================#

target_link_libraries(${TARGET_NAME} ${GTECH_DIR_LIB}/libcollader.a)

