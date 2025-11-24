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

	private:
		Window* pAppWindow;
		bool pAppRunning = true;
		LayerStack* pAppLayers;
		
		ImGuiLayer pAppImGui;

		void AppEvent(Event& event);

		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnApplicationEvent(ApplicationEvent& e);
	};

	inline static Application* CreateApplication()
	{
		return new Application();
	}

}

#endif