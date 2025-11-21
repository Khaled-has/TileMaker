#include "ImGuiLayer.h"

#include <imgui.h>
#include <imgui_impl_opengl3.h>

#include <SDL3/SDL.h>

namespace Editor {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
		ED_LOG_WARN("Destory");
	}

	void ImGuiLayer::OnAttach()
	{
		ED_LOG_WARN("Init ImGui");
		// --- ImGui Init ---
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		
		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		(void)io;

		ImGui::StyleColorsDark();

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(1440, 720);
		
		static bool first = true;
		static double last = 0;
		static double current;
		if (first)
		{
			last = SDL_GetPerformanceCounter();
			first = false;
		}
		current = SDL_GetPerformanceCounter();
		double deltaTime = (current - last) / SDL_GetPerformanceFrequency();
		last = current;

		io.DeltaTime = (float)deltaTime;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
		
		static bool show;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event)
	{

		// Mouse Moved Event
		if (Dispatch(event, MouseMovedEvent(0, 0).GetEvent()))
		{
			OnMouseMovedEvent((*(MouseMovedEvent*)&event));
		}
		// Mouse Pressed Event
		if (Dispatch(event, MousePressedEvent(0).GetEvent()))
		{
			OnMousePressedEvent((*(MousePressedEvent*)&event));
		}
		// Mouse Relessed Event
		if (Dispatch(event, MouseReleasedEvent(0).GetEvent()))
		{
			OnMouseReleasedEvent((*(MouseReleasedEvent*)&event));
		}
		// Mouse Scroll Event
		if (Dispatch(event, MouseScrollEvent(0, 0).GetEvent()))
		{
			OnMouseScrollEvent((*(MouseScrollEvent*)&event));
		}

	}


	void ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		
		ImGuiIO& io = ImGui::GetIO();
		io.AddMousePosEvent(e.GetPosX(), e.GetPosY());

	}

	void ImGuiLayer::OnMousePressedEvent(MousePressedEvent& e)
	{
		unsigned int mouse_button = 0;
		switch (e.GetButtonCode())
		{
			case ED_BUTTON_LEFT: mouse_button = 0; 
				break;
			case ED_BUTTON_RIGHT: mouse_button = 1;
				break;
			case ED_BUTTON_MIDDLE: mouse_button = 2; 
				break;
			case ED_BUTTON_X1: mouse_button = 3;
				break;
			case ED_BUTTON_X2: mouse_button = 4;
				break;
		}

		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(mouse_button, true);
	}

	void ImGuiLayer::OnMouseReleasedEvent(MouseReleasedEvent& e)
	{
		unsigned int mouse_button = 0;
		switch (e.GetButtonCode())
		{
		case ED_BUTTON_LEFT: mouse_button = 0;
			break;
		case ED_BUTTON_RIGHT: mouse_button = 1;
			break;
		case ED_BUTTON_MIDDLE: mouse_button = 2;
			break;
		case ED_BUTTON_X1: mouse_button = 3;
			break;
		case ED_BUTTON_X2: mouse_button = 4;
			break;
		}

		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(mouse_button, false);
	}

	void ImGuiLayer::OnMouseScrollEvent(MouseScrollEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseWheelEvent(e.GetYOffset(), e.GetXOffset());
	}

}