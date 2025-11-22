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
#ifdef ED_DEBUG
		// Logging system static Init
		Log::Init();
#endif

		ED_LOG_INFO("Application Started");

		// App Window Initialize

#ifdef WIN32 //  Windows Window
		pAppWindow = Editor::CreateWindowsWindow();
#elif LINUX  //   linux Window
		pAppWindow = Editor::CreateLinuxWindow();
#endif

		// Create Window
		pAppWindow->Create();

		// Application's Layers
		pAppLayers = new LayerStack();
		
		pAppLayers->Push_Back(&pAppImGui);		// ImGui Layer

	}

	Application::~Application()
	{
		delete pAppWindow;
		ED_LOG_TRACE("Application Ended");
	}

	void Application::Run()
	{
		while (pAppRunning)
		{
			pAppWindow->OnEvent(BIND_FN(Application::AppEvent));

			glClear(GL_COLOR_BUFFER_BIT);

			pAppLayers->OnUpdate();

			pAppWindow->OnUpdate();
		}
	}

	void Application::AppEvent(Event& event)
	{
		
		// Close Application
		if (Dispatch(event, KeyPressedEvent(ED_ESCAPE).GetEvent()))
		{
			if (KeyCheck<KeyPressedEvent>(ED_ESCAPE, event))
				pAppRunning = false;
		}

		if (Dispatch(event, ApplicationEvent(ED_APP_QUIT).GetEvent()))
			pAppRunning = false;

		// ===================================================================


		pAppLayers->OnEvent(event);		// Update Layers Events


	}

}