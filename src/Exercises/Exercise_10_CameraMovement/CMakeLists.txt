cmake_minimum_required(VERSION 3.15)
project(Exercise_10_CameraMovement)

set(CMAKE_CXX_STANDARD 14)

add_compile_definitions(PROJECT_NAME="${PROJECT_NAME}" PROJECT_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(${PROJECT_NAME}
        main.cpp
        rotation.h
        camera.h
        camera.cpp
        camera_controler.h
        camera_controler.cpp
        app.h
        app.cpp
        $<TARGET_OBJECTS:glad>
        )

target_link_libraries(${PROJECT_NAME} PUBLIC )
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)

