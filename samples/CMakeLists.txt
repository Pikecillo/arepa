cmake_minimum_required(VERSION 2.8.12)
project(arepa)

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

set(EXECUTABLE_OUTPUT_PATH ..)

include_directories(${AREPA_INCLUDE_DIR})

add_executable(arepa-sample-mesh-normals SampleMeshNormals.cpp)
target_link_libraries(arepa-sample-mesh-normals arepa)

add_executable(arepa-sample-gbuffer SampleGBuffer.cpp)
target_link_libraries(arepa-sample-gbuffer arepa)
