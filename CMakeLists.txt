cmake_minimum_required(VERSION 3.25)

project(TileMaker CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_language(C)

add_subdirectory(Editor)	#  TileMaker ( Editor )
add_subdirectory(Studio)	#  TileMaker ( Studio )
