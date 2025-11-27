#include "WindowsWindow.h"

#include "Log/Log.h"
#include "WindowsInput.h"

#include <imgui_impl_sdl3.h>

#ifndef ASSETS_PATH
#endif
namespace Editor {

	
	WindowsWindow::WindowsWindow()
	{
	}

	WindowsWindow::~WindowsWindow()
	{
		SDL_GL_DestroyContext(w_Context);
		SDL_DestroyWindow(w_Window);
		SDL_Quit();
		ED_LOG_TRACE("=========>  Windows window destroyed!");
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
			
			//ImGui Event
			ImGui_ImplSDL3_ProcessEvent(&ev);

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

			// Key Pressed
			if (ev.type == SDL_EVENT_KEY_DOWN)
			{
				KeyPressedEvent event(ev.key.key);
				eventFn(event);
			}

			// Key Released
			if (ev.type == SDL_EVENT_KEY_UP)
			{
				KeyReleasedEvent event(ev.key.key);
				eventFn(event);
			}

			// Key Typed
			if (ev.type == SDL_EVENT_KEY_DOWN)
			{
				KeyTypedEvent event(ev.key.key);
				eventFn(event);
			}

			// Mouse Moved Position
			if (ev.type == SDL_EVENT_MOUSE_MOTION) 
			{
				MouseMovedEvent event(ev.motion.x, ev.motion.y);
				eventFn(event);
			}

			// Mouse Pressed
			if (ev.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
			{
				MousePressedEvent event(ev.button.button);
				eventFn(event);
			}

			// Mouse Released
			if (ev.type == SDL_EVENT_MOUSE_BUTTON_UP)
			{
				MouseReleasedEvent event(ev.button.button);
				eventFn(event);
			}

			// Mouse Scroll
			if (ev.type == SDL_EVENT_MOUSE_WHEEL)
			{
				MouseScrollEvent event(ev.motion.x, ev.motion.y);
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

		w_Window = SDL_CreateWindow(w_Prop.Title.c_str(), w_Prop.Width, w_Prop.Height, SDL_WINDOW_OPENGL);
		ED_ASSERT(w_Window, "Failed create SDL window!");

		w_Context = SDL_GL_CreateContext(w_Window);
		SDL_GL_MakeCurrent(w_Window, w_Context);

		gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

		SDL_GL_SetSwapInterval(true);

		ED_LOG_TRACE("=========>  Windows window created!");
	}

	WindowsWindow* CreateWindowsWindow()
	{
		return new WindowsWindow();
	}

}