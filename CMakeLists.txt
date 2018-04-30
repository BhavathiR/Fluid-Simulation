cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)


################### Variables. ####################
# Change if you want modify path or other values. #
###################################################

set(PROJECT_NAME FluidSim3D)
# Output Variables
set(OUTPUT_DEBUG Debug/bin)
set(OUTPUT_RELEASE Release/bin)
# Folders files
set(PROJ_CPP ./src)
set(UTIL_CPP ./util/src)
set(PROJ_HEADER ./include)
set(UTIL_HEADER ./util/include)


############## CMake Project ################
#        The main options of project        #
#############################################

project(${PROJECT_NAME} CXX)

# Define Release by default.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
  message(STATUS "Build type not specified: Use Release by default.")
endif(NOT CMAKE_BUILD_TYPE)

# Definition of Macros
add_definitions(
   -D_DEBUG 
   -D_CONSOLE 
   -DUNICODE
   -D_UNICODE
)

############## CMake Project ################
#        The main options of project        #
#############################################
include_directories(~/glm/glm)


#Encontrando y linkeando OpenGL

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
link_directories(${OPENGL_LIBRARY_DIRS})
link_libraries(${OPENGL_LIBRARIES} ${OPENGL_LIBRARY})
add_definitions(${OPENGL_DEFINITIONS})

if(NOT OPENGL_FOUND)
        message(Error "OpenGL not found")
endif(NOT OPENGL_FOUND)

#Encontrando y linkeando GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_directories(${GLEW_LIBRARY_DIRS})
link_libraries(${GLEW_LIBRARIES} ${GLEW_LIBRARY})
add_definitions(${GLEW_DEFINITIONS})
if(NOT GLEW_FOUND)
 message(Error " GLEW not found")
endif(NOT GLEW_FOUND)

#Encontrando y linkeando glm

find_package(glm REQUIRED)
include_directories(${glm_INCLUDE_DIRS})
link_directories(${glm_LIBRARY_DIRS})
link_libraries(${glm_LIBRARIES} ${glm_LIBRARY})
add_definitions(${glm_DEFINITIONS})

if(NOT glm_FOUND)
        message(Error "glm not found")
endif(NOT glm_FOUND)

#Encontrando y linkeando SDL2

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
link_directories(${SDL2_LIBRARY_DIRS})
link_libraries(${SDL2_LIBRARIES} ${SDL2_LIBRARY})
add_definitions(${SDL2_DEFINITIONS})

if(NOT SDL2_FOUND)
        message(Error "SDL2 not found")
endif(NOT SDL2_FOUND)


############## Artefacts Output #################
# Defines outputs , depending Debug or Release. #
#################################################

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_DEBUG}")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_DEBUG}")
  set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_DEBUG}")
else()
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_REL}")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_REL}")
  set(CMAKE_5EXECUTABLE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_REL}")
endif()

################# Flags ################
# Defines Flags for Windows and Linux. #
########################################

if(MSVC)
   set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /W3 /MD /Od /Zi /EHsc")
   set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /W3 /GL /Od /Oi /Gy /Zi /EHsc")
endif(MSVC)
if(NOT MSVC)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
   if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
       set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
   endif()
endif(NOT MSVC)

################ Files ################
#   --   Add files to project.   --   #
#######################################

file(GLOB SRC_FILES
    ${PROJ_CPP}/*.cpp
    ${UTIL_CPP}/*.cpp
    ${UTIL_CPP}/*.vs
    ${UTIL_CPP}/*.fs
    ${PROJ_HEADER}/*.h
    ${UTIL_HEADER}/*.h
    main.cpp
)

include_directories(${PROJ_HEADER} ${UTIL_HEADER})

# Add executable to build.

add_executable(${PROJECT_NAME} ${SRC_FILES})
