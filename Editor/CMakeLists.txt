project(Editor CXX)

# ====  ImGui
file(GLOB IMGUI_CPP "external/ImGui/*.cpp")

# ===================================== #
# ==========  Add Executable ========== #

if(MSVC) 
	add_compile_options("/utf-8")
endif()


add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
				"src/main.cpp" "src/Application.cpp" "src/Log/Log.cpp" "src/Core/Platform/WindowsWindow.cpp"
				"src/Core/LayerStack.cpp" "src/Core/ImGui/ImGuiLayer.cpp" ${IMGUI_CPP}
)


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
target_include_directories(${PROJECT_NAME} PUBLIC

							"${CMAKE_SOURCE_DIR}/Editor/external/SDL3/include"		# SDL3
							"${CMAKE_SOURCE_DIR}/Editor/external/glad/include"		# OpenGL ( Glad 4.6 )

							"${CMAKE_SOURCE_DIR}/Editor/external/spdlog/include"    # Spdlog
							"${CMAKE_SOURCE_DIR}/Editor/external/ImGui"				# ImGui
							"${CMAKE_SOURCE_DIR}/Editor/external/glm"				# glm

							"${CMAKE_SOURCE_DIR}/Editor/src"						# Editor Source Code
)

# =============== Target Link Libraries ================ #
target_link_libraries(${PROJECT_NAME}
						SDL3::SDL3
						glad
)


# ==============  Platform Settings
if(WIN32) # ====>  Windows

	# SDL3 Dll copy
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
						COMMAND ${CMAKE_COMMAND} -E copy_if_different
						"${CMAKE_SOURCE_DIR}/Editor/external/SDL3/lib/x64/SDL3.dll"
						$<TARGET_FILE_DIR:${PROJECT_NAME}>
	)

	message("=====================================================================")
	message("=======================>  Build For Windows  <=======================")
	message("=====================================================================")

endif()


# =================================================== #
# =================  Compile Defines ================ #

add_compile_definitions(ED_DEBUG)		# Debug

