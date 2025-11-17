#ifndef APPLICATION_H
#define APPLICATION_H

#include "hzpch.h"
#include "Core/Platform/WindowsWindow.h"


namespace Editor
{

	class Application
	{
	public:
		Application();
		~Application();

		void Run();
		void AppEvent(Event& event);

		inline void Test() { ED_LOG_WARN("Test Success"); }
	private:
		Window* pAppWindow;
		bool pAppRunning = true;

	};

	inline static Application* CreateApplication()
	{
		return new Application();
	}

}

#endif