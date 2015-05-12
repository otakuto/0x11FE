cmake_minimum_required(VERSION 3.0.0)
project(0x11FE CXX)
add_executable(0x11FE
	main.cpp
	)
add_executable(PatternTest
	PatternObject.cpp
	Pattern.cpp
	PatternTest.cpp
	)
add_definitions("-Wall -std=c++11 -stdlib=libc++")

if(APPLE)
	set(CMAKE_CXX_COMPILER clang++)
	find_library(OPENGL_LIBRARY OpenGL)
	if(NOT OPENGL_LIBRARY)
		message(FATAL_ERROR "missing OpenGL")
	endif()
	find_library(GLUT_LIBRARY GLUT)
	if(NOT GLUT_LIBRARY)
		message(FATAL_ERROR "missing GLUT")
	endif()
	find_library(GLFW_LIBRARY glfw)
	if(NOT GLFW_LIBRARY)
		message(FATAL_ERROR "missing glfw")
	endif()
	target_link_libraries(0x11FE ${OPENGL_LIBRARY} ${GLUT_LIBRARY} ${GLFW_LIBRARY})
endif(APPLE)

file(COPY pattern/ DESTINATION pattern)
