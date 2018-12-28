#CMAKE TO MAKE A STATIC LIBRARY
#HEADER
cmake_minimum_required(VERSION 3.9.0 FATAL_ERROR)
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(TARGET_NAME glversiontest)
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
set(SDL2_LIB_DIR ${GTECH_DIR}/SDLMake2) 

if (APPLE)
	add_executable(${TARGET_NAME} glversiontest.cpp)
else()
	add_executable(${TARGET_NAME}  
    	glversiontest.cpp
    	$ENV{GTECH_ROOT}/3rd/include/glad/glad.cpp
	)
endif()
set(CMAKE_VERBOSE_MAKEFILE TRUE)




#========= INCLUDE ==============#

target_include_directories(${TARGET_NAME} PUBLIC ${GLM_INC_DIR})
target_include_directories(${TARGET_NAME} PUBLIC ${COLLADER_INC_DIR})
target_include_directories(${TARGET_NAME} PUBLIC ${SDL2_INC_DIR})
target_include_directories(${TARGET_NAME} PUBLIC ${GTECH_DIR_INC})

#========== LINK ================#

target_link_libraries(${TARGET_NAME}
	${GTECH_DIR_LIB}/libcollader.a
	${GTECH_DIR_LIB}/libsdlwrapper.a
	${GTECH_DIR_LIB}/libSDL_image.a
	${GTECH_DIR_LIB}/libSDL2.a
	${GTECH_DIR_LIB}/libShaderMan.a
	${GTECH_DIR_LIB}/libjpeg.a 
	${GTECH_DIR_LIB}/libpng.a 
	${GTECH_DIR_LIB}/libz.a
	${GTECH_DIR_LIB}/libtiff_static.a 
	"-lm -lpthread"
	)
set(CMAKE_BUILD_TYPE Debug)
if (UNIX AND NOT APPLE)
	target_link_libraries(${TARGET_NAME} "-ldl")
endif()

get_filename_component(COLLADER_TEST_RESOURCE ${ROOT_DIR}/../resources ABSOLUTE)
target_compile_definitions(${TARGET_NAME} PUBLIC RESOURCES_DIR="${COLLADER_TEST_RESOURCE}")


#========== MacOS ===============#
if (APPLE)
	target_link_libraries(${TARGET_NAME} iconv)
	target_link_libraries(${PROJECT_NAME}
		"-framework Carbon" "-framework ForceFeedback" "-framework IOKit" "-framework Cocoa" "-framework CoreVideo"
		"-framework AudioToolbox" "-framework CoreAudio" "-framework CoreFoundation" "-framework AppKit"  
		"-framework OpenGL")
endif()

