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

#GLM
set(GLM_DIR "${ROOT_DIR}/../GLM")


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
