#include "Application.h"

#include "Core/Events/KeyEvent.h"
#include "Core/Events/ApplicationEvent.h"
#include "Core/Events/MouseEvent.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl3.h"

#include "Core/Platform/Windows/WindowsInput.h"

namespace Editor
{

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;

#ifdef ED_DEBUG
		// Logging system static Init
		Log::Init();
#endif

		ED_LOG_INFO("Application Started");

		// App Window Initialize

#ifdef WIN32 //  Windows Window & Input
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
		// Application Events
		EventDispatcher dispatcher(event);

		dispatcher.Dispatcher<KeyPressedEvent>(BIND_FN(Application::OnKeyPressedEvent));
		dispatcher.Dispatcher<ApplicationEvent>(BIND_FN(Application::OnApplicationEvent));

		// Update Layers Events
		pAppLayers->OnEvent(event);
	}

	bool Application::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == ED_ESCAPE)
			pAppRunning = false;

		return true;
	}

	bool Application::OnApplicationEvent(ApplicationEvent& e)
	{
		if (e.GetAppCode() == ED_APP_QUIT)
			pAppRunning = false;

		return false;
	}

}