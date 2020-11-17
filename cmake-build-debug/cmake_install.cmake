# Install script for directory: E:/Infa/Studia/Rok4/Programowanie Grafiki 3D

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/3DGraphicsExamples")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("E:/Infa/Studia/Rok4/Programowanie Grafiki 3D/cmake-build-debug/src/3rdParty/src/glfw3/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("E:/Infa/Studia/Rok4/Programowanie Grafiki 3D/cmake-build-debug/src/Application/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("E:/Infa/Studia/Rok4/Programowanie Grafiki 3D/cmake-build-debug/src/Exercises/Exercise_01_Triangle/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("E:/Infa/Studia/Rok4/Programowanie Grafiki 3D/cmake-build-debug/src/Exercises/Exercise_02_Colors/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("E:/Infa/Studia/Rok4/Programowanie Grafiki 3D/cmake-build-debug/src/Exercises/Exercise_03_Indices/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("E:/Infa/Studia/Rok4/Programowanie Grafiki 3D/cmake-build-debug/src/Exercises/Exercise_04_Uniforms/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("E:/Infa/Studia/Rok4/Programowanie Grafiki 3D/cmake-build-debug/src/Exercises/Exercise_05_PVM/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("E:/Infa/Studia/Rok4/Programowanie Grafiki 3D/cmake-build-debug/src/Exercises/Exercise_06_Pyramid/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("E:/Infa/Studia/Rok4/Programowanie Grafiki 3D/cmake-build-debug/src/Exercises/Exercise_07_Backface/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("E:/Infa/Studia/Rok4/Programowanie Grafiki 3D/cmake-build-debug/src/Exercises/Exercise_08_WindowResize/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("E:/Infa/Studia/Rok4/Programowanie Grafiki 3D/cmake-build-debug/src/Exercises/Exercise_09_Zooming/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("E:/Infa/Studia/Rok4/Programowanie Grafiki 3D/cmake-build-debug/src/Exercises/Exercise_10_CameraMovement/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("E:/Infa/Studia/Rok4/Programowanie Grafiki 3D/cmake-build-debug/src/Exercises/Exercise_11_PyramidAnimation/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("E:/Infa/Studia/Rok4/Programowanie Grafiki 3D/cmake-build-debug/src/Exercises/Exercise_11_2_SolarSystem/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "E:/Infa/Studia/Rok4/Programowanie Grafiki 3D/cmake-build-debug/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
