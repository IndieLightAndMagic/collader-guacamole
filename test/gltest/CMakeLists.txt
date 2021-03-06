#CMAKE TO MAKE A STATIC LIBRARY
#HEADER
cmake_minimum_required(VERSION 3.9.0 FATAL_ERROR)
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
set(GTECH_DIR_SRC ${GTECH_DIR}/3rd/src)
set(GTECH_DIR_LIB ${GTECH_DIR}/3rd/lib)
set(GTECH_DIR_INC ${GTECH_DIR}/3rd/include)


add_executable(${TARGET_NAME}  

    gltest.cpp
    thescene.cpp
    datastructures.cpp
    ${GTECH_DIR_SRC}/glad.c
)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_BUILD_TYPE Debug)



#========= INCLUDE ==============#

target_include_directories(${TARGET_NAME} PUBLIC ${GTECH_DIR_INC})

#========== LINK ================#

target_link_libraries(${TARGET_NAME}
    ${GTECH_DIR_LIB}/libcollader.a ${GTECH_DIR_LIB}/libShaderMan.a ${GTECH_DIR_LIB}/libglfw3.a "-liconv" "-lm"
        )

get_filename_component(COLLADER_TEST_RESOURCE ${ROOT_DIR}/../resources ABSOLUTE)
target_compile_definitions(${TARGET_NAME} PUBLIC RESOURCES_DIR="${COLLADER_TEST_RESOURCE}")


#========== MacOS ===============#

target_link_libraries(${PROJECT_NAME}
        "-framework Carbon" "-framework ForceFeedback" "-framework IOKit" "-framework Cocoa" "-framework CoreVideo"
        "-framework AudioToolbox" "-framework CoreAudio" "-framework CoreFoundation" "-framework AppKit"  
        "-framework OpenGL")

