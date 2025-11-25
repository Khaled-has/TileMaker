#ifndef APPLICATION_H
#define APPLICATION_H

#include "hzpch.h"
#include "Core/Platform/Windows/WindowsWindow.h"
#include "Core/LayerStack.h"

#include "Core/ImGui/ImGuiLayer.h"
#include "Core/Events/Input.h"

namespace Editor
{

	class Application
	{
	public:
		Application();
		~Application();

		void Run();

		inline Window* GetWindow() { return pAppWindow; }

		inline static Application* Get() { return s_Instance; }

	private:
		static Application* s_Instance;

		Window* pAppWindow;
		LayerStack* pAppLayers;

		ImGuiLayer pAppImGui;

		bool pAppRunning = true;

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