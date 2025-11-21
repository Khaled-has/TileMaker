#ifndef APPLICATION_H
#define APPLICATION_H

#include "hzpch.h"
#include "Core/Platform/WindowsWindow.h"
#include "Core/LayerStack.h"

#include "Core/ImGui/ImGuiLayer.h"


namespace Editor
{

	class Application
	{
	public:
		Application();
		~Application();

		void Run();
		void AppEvent(Event& event);

	private:
		Window* pAppWindow;
		bool pAppRunning = true;
		LayerStack* pAppLayers;
		
		ImGuiLayer pAppImGui;

	};

	inline static Application* CreateApplication()
	{
		return new Application();
	}

}

#endif