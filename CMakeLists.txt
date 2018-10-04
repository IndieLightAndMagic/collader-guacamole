#CMAKE TO MAKE A STATIC LIBRARY
#HEADER
cmake_minimum_required(VERSION 3.9.0 FATAL_ERROR)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(TARGET_NAME collader)
project(${TARGET_NAME})
set(CMAKE_CXX_STANDARD 17)

#Installation directory 
get_filename_component(GTECH_DIR $ENV{GTECH_ROOT} ABSOLUTE)
set(GTECH_DIR_LIB ${GTECH_DIR}/3rd/lib/)
set(GTECH_DIR_INC ${GTECH_DIR}/3rd/include/collader)

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
    collader.h 
    collader.cpp 
    library_visual_scenes.cpp 
    library_lights.cpp 
    library_cameras.cpp 
    library_materials.cpp 
    library_effects.cpp 
    library_geometries.cpp 
    library_images.cpp 
    tinyxml2/tinyxml2.cpp 
    tinyxml2/tinyxml2.h
    idname.h 
    idname.cpp
    camera.h 
    camera.cpp 
    light.h
    light.cpp
    mesh.h
    mesh.cpp
    effect.h
    effect.cpp
    material.h
    material.cpp    
    node.h
    node.cpp
    scene.h
    scene.cpp
    glcollader.cpp
)
target_include_directories(${TARGET_NAME} PUBLIC ${GLM_DIR})

file(MAKE_DIRECTORY ${GTECH_DIR})
file(MAKE_DIRECTORY ${GTECH_DIR_LIB})
file(MAKE_DIRECTORY ${GTECH_DIR_INC})


#POST BUILD COMMANDS 
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy lib${TARGET_NAME}.a ${GTECH_DIR}/3rd/lib
	COMMAND ${CMAKE_COMMAND} -E copy ${ROOT_DIR}/*.h ${GTECH_DIR}/3rd/include/collader
	) 

add_executable(${TARGET_NAME}test  

    collader.h 
    collader.cpp 
    library_visual_scenes.cpp 
    library_lights.cpp 
    library_cameras.cpp 
    library_materials.cpp 
    library_effects.cpp 
    library_geometries.cpp 
    library_images.cpp 
    tinyxml2/tinyxml2.cpp 
    tinyxml2/tinyxml2.h
    idname.h 
    idname.cpp
    camera.h 
    camera.cpp 
    light.h
    light.cpp
    mesh.h
    mesh.cpp
    effect.h
    effect.cpp
    material.h
    material.cpp    
    node.h
    node.cpp
    scene.h
    scene.cpp
    glcollader.cpp
    colladertest.cpp
)

target_include_directories(${TARGET_NAME}test PUBLIC ${GLM_DIR})
