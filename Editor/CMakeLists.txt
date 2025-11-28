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
				"src/main.cpp" "src/Application.cpp" "src/Log/Log.cpp" "src/Core/Platform/Windows/WindowsWindow.cpp"
				"src/Core/LayerStack.cpp" "src/Core/ImGui/ImGuiLayer.cpp" "src/Core/Platform/Windows/WindowsInput.cpp"
				${IMGUI_CPP}
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
	message("====================>  Build Editor For Windows  <===================")
	message("=====================================================================")

endif()


# =================================================== #
# =================  Compile Defines ================ #

add_compile_definitions(ED_DEBUG)		# Debug

if (WIN32)
	add_compile_definitions(ED_WINDOW_SDL3)
endif()

add_compile_definitions(ASSETS_PATH="${CMAKE_SOURCE_DIR}/Editor/assets/")	# Assets_Path
