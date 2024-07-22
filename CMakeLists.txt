cmake_minimum_required(VERSION 3.10)

project(TransportConApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(TransportConApp src/TransportConApp.cpp)

if(WIN32)
	target_compile_options(TransportConApp PRIVATE /utf-8)
endif()