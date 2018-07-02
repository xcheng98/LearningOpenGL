cmake_minimum_required(VERSION 3.9)
project(opengl_hello_texture)

set(CMAKE_CXX_STANDARD 11)

add_executable(opengl_hello_texture main4.cpp load_image_helper.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(opengl_hello_texture ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} glfw glew)