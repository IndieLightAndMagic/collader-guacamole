#CMAKE TO MAKE A STATIC LIBRARY
#HEADER
cmake_minimum_required(VERSION 3.9.0 FATAL_ERROR)
set(TARGET_NAME collader)
project(${TARGET_NAME})
set(CMAKE_CXX_STANDARD 17)

#Installation directory 
get_filename_component(GTECH_DIR $ENV{GTECH_ROOT} ABSOLUTE)
set(GTECH_DIR_LIB ${GTECH_DIR}/3rd/lib/)
set(GTECH_DIR_INC ${GTECH_DIR}/3rd/include/)
set(GTECH_DIR_INC_COLLADER ${GTECH_DIR}/3rd/include/collader)

#DIRECTORIES
get_filename_component(ROOT_DIR "." ABSOLUTE)
message(STATUS "SYSTEM NAME: ${CMAKE_SYSTEM_NAME}")
message(STATUS "ROOT_DIR: ${ROOT_DIR}")
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "-----------------------------")

#GLM
set(GLM_DIR "${GTECH_DIR}/GLM")


add_library(${TARGET_NAME} STATIC
 
    collader.cpp 
    library_visual_scenes.cpp 
    library_lights.cpp 
    library_cameras.cpp 
    library_materials.cpp 
    library_effects.cpp 
    library_geometries.cpp 
    library_images.cpp 
    tinyxml2/tinyxml2.cpp 
    idname.cpp
    camera.cpp 
    light.cpp
    mesh.cpp
    effect.cpp
    material.cpp 
    node.cpp
    scene.cpp
    glcollader.cpp
    newparam.cpp

)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_BUILD_TYPE Debug)
target_include_directories(${TARGET_NAME} PUBLIC 
    ${GLM_DIR}
    ${GTECH_DIR_INC}
    )

file(MAKE_DIRECTORY ${GTECH_DIR})
file(MAKE_DIRECTORY ${GTECH_DIR_LIB})
file(MAKE_DIRECTORY ${GTECH_DIR_INC_COLLADER})
file(MAKE_DIRECTORY ${GTECH_DIR_INC_COLLADER}/tinyxml2)


#POST BUILD COMMANDS 
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy lib${TARGET_NAME}.a ${GTECH_DIR}/3rd/lib
	COMMAND ${CMAKE_COMMAND} -E copy ${ROOT_DIR}/*.h ${GTECH_DIR}/3rd/include/collader
	COMMAND ${CMAKE_COMMAND} -E copy ${ROOT_DIR}/tinyxml2/*.h ${GTECH_DIR}/3rd/include/collader/tinyxml2
    ) 

