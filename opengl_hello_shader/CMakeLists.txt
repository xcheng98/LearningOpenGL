cmake_minimum_required(VERSION 3.9)
project(opengl_hello_shader)

set(CMAKE_CXX_STANDARD 11)

add_executable(opengl_hello_shader main.cpp shaderProgram.h)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(opengl_hello_shader ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} glfw glew)