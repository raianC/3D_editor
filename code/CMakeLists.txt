cmake_minimum_required(VERSION 3.10)
project(computer_science)

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE debug)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")


include_directories(include/)

add_subdirectory(glfw-3.5.1)

add_library(Face src/Face.cpp)
add_library(Editor3D src/Editor3D.cpp)
add_library(Mesh src/Mesh.cpp)
add_library(Scene src/Scene.cpp)
add_library(Vertex src/Vertex.cpp)
add_library(HalfEdge src/HalfEdge.cpp)
add_library(PlyLoader src/PlyLoader.cpp)
add_library(ObjLoader src/ObjLoader.cpp)
add_library(Loader src/Loader.cpp)
add_library(glad src/glad.c)
add_library(cam src/camera.cpp)
find_package(OpenGL REQUIRED)

target_link_libraries(Mesh PRIVATE
    Vertex
    Face
    HalfEdge
)

target_link_libraries(Scene PRIVATE
    glfw
    glad
    OpenGL::GL
)

add_executable(main src/main.cpp)

target_link_libraries(main Face Vertex HalfEdge Mesh glad glfw Scene Editor3D cam Loader PlyLoader ObjLoader OpenGL::GL)
