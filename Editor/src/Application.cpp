#include "Application.h"

#include "Core/Events/KeyEvent.h"
#include "Core/Events/ApplicationEvent.h"
#include "Core/Events/MouseEvent.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl3.h"

namespace Editor
{

	Application::Application()
	{
		// Logging system static Init
		Log::Init();
		ED_LOG_INFO("Application Started");

		// App Window Initialize

#ifdef WIN32 //  Windows Window
		pAppWindow = Editor::CreateWindowsWindow();
#elif LINUX //   linux Window

#endif

		// Create Window
		pAppWindow->Create();
		
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

	}

	Application::~Application()
	{
		ED_LOG_TRACE("Application Ended");
	}

	void Application::Run()
	{
		while (pAppRunning)
		{
			pAppWindow->OnEvent(BIND_FN(Application::AppEvent));

			pAppWindow->OnUpdate();
		}
	}

	void Application::AppEvent(Event& event)
	{
		
		// Close Application
		if (Dispatch(event, KeyPressedEvent(ED_ESCAPE).GetEvent()))
			pAppRunning = false;

		if (Dispatch(event, ApplicationEvent(ED_APP_QUIT).GetEvent()))
			pAppRunning = false;

		// ===================================================================
		

	}

}