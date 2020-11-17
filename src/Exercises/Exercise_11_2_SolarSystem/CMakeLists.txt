cmake_minimum_required(VERSION 3.15)
project(Exercise_11_2_SolarSystem)

set(CMAKE_CXX_STANDARD 14)

add_compile_definitions(PROJECT_NAME="${PROJECT_NAME}" PROJECT_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(${PROJECT_NAME}
        main.cpp
        Headers/rotation.h
        Headers/camera.h
        Source/camera.cpp
        Headers/camera_controler.h
        Source/camera_controler.cpp
        Headers/pyramid.h
        Source/pyramid.cpp
        Headers/app.h
        Source/app.cpp
        $<TARGET_OBJECTS:glad>
        )

target_link_libraries(${PROJECT_NAME} PUBLIC )
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)

