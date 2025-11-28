cmake_minimum_required(VERSION 3.25)

project(TileMaker CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_language(C)

add_subdirectory(Editor)	#  TileMaker ( Editor )
add_subdirectory(Studio)	#  TileMaker ( Studio )

# ===================================== #
# ==========  Link Libraries ========== #

# ====  SDL3
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/Editor/external/SDL3/cmake")
find_package(SDL3 REQUIRED CONFIG COMPONENTS SDL3)

# ====  OpengGL Glad 4.6
add_library(glad STATIC
			"${CMAKE_SOURCE_DIR}/Editor/external/glad/src/glad.c"
)

target_include_directories(glad PUBLIC
							"${CMAKE_SOURCE_DIR}/Editor/external/glad/include"
)


# ============= Target Include Diractorise ============= #
target_include_directories(Editor PUBLIC

							"${CMAKE_SOURCE_DIR}/Editor/external/SDL3/include"		# SDL3
							"${CMAKE_SOURCE_DIR}/Editor/external/glad/include"		# OpenGL ( Glad 4.6 )

							"${CMAKE_SOURCE_DIR}/Editor/external/spdlog/include"    # Spdlog
							"${CMAKE_SOURCE_DIR}/Editor/external/ImGui"				# ImGui
							"${CMAKE_SOURCE_DIR}/Editor/external/glm"				# glm

							"${CMAKE_SOURCE_DIR}/Editor/src"						# Editor Source Code
)

# =============== Target Link Libraries ================ #
target_link_libraries(Editor
						SDL3::SDL3
						glad
)
