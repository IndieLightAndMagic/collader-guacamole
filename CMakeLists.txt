cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(TARGET_NAME collader)
project(
    ${TARGET_NAME}
    VERSION 0.0.1
    DESCRIPTION "QQE Engine: Collada Importer from Blender."
    HOMEPAGE_URL "github.com/IndieLightAndMagic/collader-guacamole.git"
    LANGUAGES CXX
    )
    

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_STANDARD 17)

find_package(tinyxml2 REQUIRED)
find_package(glm REQUIRED)

file(GLOB CPP_SOURCES ${CMAKE_SOURCE_DIR}/*.cpp)

function(PrintRuler)
    message(STATUS "*****************************************")
endfunction()

PrintRuler()
message(STATUS "Adding the following files:")
foreach(CPP_SOURCE ${CPP_SOURCES})
    message(STATUS ${CPP_SOURCE})
endforeach()


PrintRuler()
if (APPLE)
    message(STATUS "MacOS operative System.")
endif()



add_library(${TARGET_NAME} STATIC
    ${CPP_SOURCES}
)
PrintRuler()
if (APPLE)
    find_path(TINYXML2_INCLUDE_DIR NAMES tinyxml2.h)
    target_include_directories(${TARGET_NAME} PRIVATE ${TINYXML2_INCLUDE_DIR})
endif()


