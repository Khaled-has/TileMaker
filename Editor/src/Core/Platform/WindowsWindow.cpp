#include "WindowsWindow.h"

#include "Log/Log.h"

#include "Core/Events/KeyEvent.h"
#include "Core/Events/ApplicationEvent.h"
#include "Core/Events/MouseEvent.h"

namespace Editor {

	
	WindowsWindow::WindowsWindow()
	{
	}

	WindowsWindow::~WindowsWindow()
	{
	}

	void WindowsWindow::OnUpdate()
	{
		SDL_GL_SwapWindow(w_Window);
	}

	void WindowsWindow::OnEvent(EventFn eventFn) const
	{

		SDL_Event ev;

		while (SDL_PollEvent(&ev))
		{

			// Application Check
			{
				// Quit
				if (ev.type == SDL_EVENT_QUIT)
				{
					ApplicationEvent event(ED_APP_QUIT);
					ED_LOG_INFO(event.ToString());
					eventFn(event);
					break;
				}
			}

			// Key Pressed Check
			if (ev.type == SDL_EVENT_KEY_DOWN)
			{
				KeyPressedEvent event(ev.key.key);
				ED_LOG_INFO(event.ToString());
				eventFn(event);
			}

			// Key Released
			if (ev.type == SDL_EVENT_KEY_UP)
			{
				KeyReleasedEvent event(ev.key.key);
				ED_LOG_INFO(event.ToString());
				eventFn(event);
			}

			// Mouse Moved Position
			if (ev.type == SDL_EVENT_MOUSE_MOTION) 
			{
				MouseMovedEvent event(ev.motion.x, ev.motion.y);
				ED_LOG_INFO(event.ToString());
				eventFn(event);
			}

			// Mouse Pressed
			if (ev.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
			{
				MousePressedEvent event(ev.button.button);
				ED_LOG_INFO(event.ToString());
				eventFn(event);
			}

			// Mouse Released
			if (ev.type == SDL_EVENT_MOUSE_BUTTON_UP)
			{
				MouseReleasedEvent event(ev.button.button);
				ED_LOG_INFO(event.ToString());
				eventFn(event);
			}

			// Mouse Scroll
			if (ev.type == SDL_EVENT_MOUSE_WHEEL)
			{
				MouseScrollEvent event(ev.motion.x, ev.motion.y);
				ED_LOG_INFO(event.ToString());
				eventFn(event);
			}

		}

	}

	void WindowsWindow::Create()
	{
		SDL_Init(SDL_INIT_VIDEO);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		SDL_GL_MakeCurrent(w_Window, w_Context);

		gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

		SDL_GL_SetSwapInterval(true);

		ED_ASSERT(!w_Window, "Failed create SDL window");

		w_Window = SDL_CreateWindow(w_Prop.Title.c_str(), w_Prop.Width, w_Prop.Height, SDL_WINDOW_OPENGL);

		ED_LOG_INFO("Windows window created");
	}

	WindowsWindow* CreateWindowsWindow()
	{
		return new WindowsWindow();
	}

}