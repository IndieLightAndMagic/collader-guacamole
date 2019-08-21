#CMAKE TO MAKE A STATIC LIBRARY
#HEADER
cmake_minimum_required(VERSION 3.9.0 FATAL_ERROR)
set(TARGET_NAME colladertest)
project(${TARGET_NAME})
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_BUILD_TYPE DEBUG)
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


#GLM
#COLLADER
add_executable(${TARGET_NAME}  

    colladertest.cpp
	../../camera.cpp
	../../image.cpp
	../../library_lights.cpp		
    ../../mesh.cpp
	../../collader.cpp
	../../library_cameras.cpp
	../../library_materials.cpp
	../../newparam.cpp
	../../effect.cpp
	../../library_effects.cpp
	../../library_visual_scenes.cpp
	../../node.cpp
	../../glcollader.cpp
	../../library_geometries.cpp
	../../light.cpp
	../../scene.cpp
	../../idname.cpp
	../../library_images.cpp
	../../material.cpp


    
)
target_include_directories(${TARGET_NAME} PUBLIC
	/usr/local/include
	../..
	)

target_link_libraries(${TARGET_NAME}
	/usr/local/lib/libtinyxml2.a		

	)
