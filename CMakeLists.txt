cmake_minimum_required(VERSION 3.15)
include(ExternalProject)
project(3DGraphicsExamples CXX C)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 11)

set(3rdParty ${PROJECT_SOURCE_DIR}/src/3rdParty)
include_directories(${PROJECT_SOURCE_DIR}/src/3rdParty/include ${PROJECT_SOURCE_DIR}/src)

file(GLOB_RECURSE glad_SOURCES "${PROJECT_SOURCE_DIR}/src/3rdParty/src/glad/*.c")
list(APPEND 3rdParty_SOURCES ${glad_SOURCES})


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${3rdParty}/src/glfw3)


add_library(glad OBJECT ${glad_SOURCES})

find_package(OpenGL REQUIRED)

link_libraries(OpenGL::GL glfw)
add_subdirectory(src/Application)

link_libraries(application)
add_subdirectory(src/Exercises/Exercise_01_Triangle)
add_subdirectory(src/Exercises/Exercise_02_Colors)
add_subdirectory(src/Exercises/Exercise_03_Indices)
add_subdirectory(src/Exercises/Exercise_04_Uniforms)
add_subdirectory(src/Exercises/Exercise_05_PVM)
add_subdirectory(src/Exercises/Exercise_06_Pyramid)
add_subdirectory(src/Exercises/Exercise_07_Backface)
add_subdirectory(src/Exercises/Exercise_08_WindowResize)
add_subdirectory(src/Exercises/Exercise_09_Zooming)
add_subdirectory(src/Exercises/Exercise_10_CameraMovement)
add_subdirectory(src/Exercises/Exercise_11_PyramidAnimation)
add_subdirectory(src/Exercises/Exercise_11_2_SolarSystem)
add_subdirectory(src/Exercises/Exercise_12_TexturedPyramid)
add_subdirectory(src/Exercises/Exercise_13_PhongDiffuseLightning)
