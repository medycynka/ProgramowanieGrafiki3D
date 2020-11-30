cmake_minimum_required(VERSION 3.15)
project(Exercise_13_PhongDiffuseLightning)

set(CMAKE_CXX_STANDARD 14)

add_compile_definitions(PROJECT_NAME="${PROJECT_NAME}" PROJECT_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(${PROJECT_NAME}
        main.cpp
        Headers/rotation.h
        Headers/camera.h
        Headers/camera_controler.h
        Headers/quad.h
        Headers/app.h
        Source/camera.cpp
        Source/camera_controler.cpp
        Source/app.cpp
        Source/quad.cpp
        $<TARGET_OBJECTS:glad>
        )

target_link_libraries(${PROJECT_NAME} PUBLIC )
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)

