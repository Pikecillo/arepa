cmake_minimum_required(VERSION 2.8.12)
project(arepa)

set(OpenGL_GL_PREFERENCE LEGACY)

find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIRS})
    link_libraries(${OPENGL_LIBRARIES})
endif()

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

find_package(GLUT REQUIRED)
if (GLUT_FOUND)
    include_directories(${GLUT_INCLUDE_DIRS})
    link_libraries(${GLUT_LIBRARIES})
endif()

include_directories(include)
file(GLOB SOURCES "src/*.cpp")
set(CMAKE_CXX_FLAGS "-std=c++0x")
add_library(arepa STATIC ${SOURCES})

set(AREPA_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(samples)