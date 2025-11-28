#include "WindowsWindow.h"

#include "Log/Log.h"
#include "WindowsInput.h"

#include <imgui_impl_sdl3.h>

#include <SDL3/SDL_system.h>
#include <Windows.h>

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

		w_Window = SDL_CreateWindow(
			w_Prop.Title.c_str(), 
			w_Prop.Width, w_Prop.Height, 
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
		);

		ED_ASSERT(w_Window, "Failed create SDL window!");

		w_Context = SDL_GL_CreateContext(w_Window);
		SDL_GL_MakeCurrent(w_Window, w_Context);

		gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

		SDL_GL_SetSwapInterval(true);


		// Some window details ( WIN32 )
		SDL_PropertiesID props = SDL_GetWindowProperties(w_Window);

		HWND hwnd = (HWND)SDL_GetPointerProperty(
			props,
			SDL_PROP_WINDOW_WIN32_HWND_POINTER,
			NULL
		);

		// Update window's size for fixe some ui components
		SDL_SetWindowSize(w_Window, w_Prop.Width, w_Prop.Height - 10);
		SDL_SetWindowSize(w_Window, w_Prop.Width, w_Prop.Height);

		ED_ASSERT(hwnd, "Failed to take HWND WIN32 for SDL3 window");

		LONG style = GetWindowLong(hwnd, GWL_STYLE);

		style &= ~WS_CAPTION;
		style &= ~WS_SYSMENU;
		style &= ~WS_MAXIMIZEBOX;
		style &= ~WS_MINIMIZEBOX;

		SetWindowLong(hwnd, GWL_STYLE, style);

		SetWindowPos(
			hwnd, NULL,
			0, 0, 0, 0,
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED
			);

		ED_LOG_TRACE("=========>  Windows window created!");
	}

	WindowsWindow* CreateWindowsWindow()
	{
		return new WindowsWindow();
	}

	void handleWindowSize(SDL_Window* win, SDL_Event* ev, unsigned int side)
	{

		int w, h, x, y;
		SDL_GetWindowSize(win, &w, &h);

		if (ev->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {

			// Right
			if (side == 0)
			{
				SDL_SetWindowSize(win, w + ev->motion.xrel, h);
				ED_LOG_TRACE("{0} | {1}", ev->motion.xrel, ev->motion.yrel);
			}
		}
	}

}