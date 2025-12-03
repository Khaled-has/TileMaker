#include "WindowsWindow.h"

#ifdef WIN32

#include "Log/Log.h"
#include "WindowsInput.h"

#include <imgui_impl_sdl3.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_system.h>
#include <Windows.h>
#include <windowsx.h>

#include <iostream>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

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

	void WIN32CustomProcess(SDL_Window* win, SDL_Event* ev)
	{
		// Window move
		if (ev->type == SDL_EVENT_MOUSE_BUTTON_DOWN && (ev->motion.y < 40))
		{
			SDL_Window* focus = SDL_GetKeyboardFocus();

			if (focus == win)
			{
				// Window move process
				SDL_PropertiesID props = SDL_GetWindowProperties(win);
				HWND hwnd = (HWND)SDL_GetPointerProperty(
					props,
					SDL_PROP_WINDOW_WIN32_HWND_POINTER,
					NULL
				);

				ED_ASSERT(hwnd, "Failed to take HWND WIN32 for SDL3 window");

				ReleaseCapture();
				SendMessage(hwnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
			}
		}

		// Minimum window size
		if (ev->type == SDL_EVENT_WINDOW_RESIZED)
		{
			int w, h;
			SDL_GetWindowSize(win, &w, &h);

			if (w < 1440)
			{
				SDL_SetWindowSize(win, 1440, h);
			}
			if (h < 720)
			{
				SDL_SetWindowSize(win, w, 720);
			}
			
		}

	}

	void WindowsWindow::SetCallbackEventFunc(EventFn eventFn)
	{

		SDL_Event ev;
		SDL_PumpEvents();
		while (SDL_PollEvent(&ev))
		{
			// ImGui Event
			ImGui_ImplSDL3_ProcessEvent(&ev);

			// Some WIN32 process
			WIN32CustomProcess(w_Window, &ev);

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
				// Window size
				int w, h;
				SDL_GetWindowSize(w_Window, &w, &h);
				w_Prop.Width = w; w_Prop.Height = h;
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

	static WNDPROC g_OriginalWndProc = nullptr;
	// WIN32 For ReSizeable The Window
	static LRESULT CALLBACK SDLWin32Proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_NCHITTEST:
		{
			POINT ptMouse = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
			ScreenToClient(hwnd, &ptMouse);

			RECT rc;
			GetClientRect(hwnd, &rc);

			const LONG border = 8;
			bool top = ptMouse.y < border;
			bool bottom = ptMouse.y >= rc.bottom - border;
			bool left = ptMouse.x < border;
			bool right = ptMouse.x >= rc.right - border;

			if (top && left) return HTTOPLEFT;
			if (top && right) return HTTOPRIGHT;
			if (bottom && left) return HTBOTTOMLEFT;
			if (bottom && right) return HTBOTTOMRIGHT;
			if (top) return HTTOP;
			if (bottom) return HTBOTTOM;
			if (left) return HTLEFT;
			if (right) return HTRIGHT;
		}
		}

		return CallWindowProcW((WNDPROC)g_OriginalWndProc, hwnd, msg, wParam, lParam);
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
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_BORDERLESS
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

		ED_ASSERT(hwnd, "Failed to take HWND WIN32 for SDL3 window");

		// Border Color ( Only Windows 11 )
		DWORD border = RGB(100, 100, 100);
		DwmSetWindowAttribute(hwnd, DWMWA_BORDER_COLOR, &border, sizeof(border));

		MARGINS margins = { 1, 1, 1, 1 };
		DwmExtendFrameIntoClientArea(hwnd, &margins);

		// Add Corner for the window ( Only Windows 11 )
		DWM_WINDOW_CORNER_PREFERENCE cornerPreference = DWMWCP_ROUND;
		DwmSetWindowAttribute(hwnd, DWMWA_WINDOW_CORNER_PREFERENCE, &cornerPreference, sizeof(cornerPreference));

		SetWindowPos(
			hwnd, NULL,
			0, 0, 0, 0,
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED
			);

		// Set Window Native ReSizeable System
		g_OriginalWndProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)SDLWin32Proc);

		// Update window's size for fixe some ui components
		SDL_SetWindowSize(w_Window, w_Prop.Width - 40, w_Prop.Height - 20);
		SDL_SetWindowSize(w_Window, w_Prop.Width, w_Prop.Height);

		ED_LOG_TRACE("=========>  Windows window created!");
	}

	void SetWin32Show(SDL_Window* win, int flag)
	{
		SDL_PropertiesID props = SDL_GetWindowProperties(win);
		HWND hwnd = (HWND)SDL_GetPointerProperty(
			props,
			SDL_PROP_WINDOW_WIN32_HWND_POINTER,
			NULL
		);

		ED_ASSERT(hwnd, "Failed Take HWND");
		ShowWindow(hwnd, flag);

		// TitleBar Color
		DWORD border = RGB(100, 100, 100);
		DwmSetWindowAttribute(hwnd, DWMWA_BORDER_COLOR, &border, sizeof(border));

		MARGINS margins = { 1, 1, 1, 1 };
		DwmExtendFrameIntoClientArea(hwnd, &margins);

		DWM_WINDOW_CORNER_PREFERENCE cornerPreference = DWMWCP_ROUND;
		DwmSetWindowAttribute(hwnd, DWMWA_WINDOW_CORNER_PREFERENCE, &cornerPreference, sizeof(cornerPreference));

		// Update window's size for fixe some ui components
		SetWindowPos(
			hwnd, NULL,
			0, 0, 0, 0,
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED
		);

		int w, h;
		SDL_GetWindowSize(win, &w, &h);
		SDL_SetWindowSize(win, w - 20, h - 10);
		SDL_SetWindowSize(win, w, h);
	}

	void WindowsWindow::CustomBar(bool* pRunning)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8.f, 15.f));

		if (ImGui::BeginMainMenuBar())
		{

		
			ImGui::Spacing();
			ImGui::Image((ImTextureRef)w_Prop.icon.GetID(), ImVec2(50, 50));
			ImGui::Spacing();

			ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 8.0f);
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("FFF"))
				{
					ImGui::EndTabItem();
				}


				ImGui::EndMenu();
			}
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 8.0f);
			if (ImGui::BeginMenu("Edite"))
			{
				if (ImGui::MenuItem("FFF"))
				{
					ImGui::EndTabItem();
				}


				ImGui::EndMenu();
			}
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 8.0f);
			if (ImGui::BeginMenu("Window"))
			{
				if (ImGui::MenuItem("FFF"))
				{
					ImGui::EndTabItem();
				}


				ImGui::EndMenu();
			}
			// Title
			ImGui::SameLine(((ImGui::GetWindowWidth() / 2) - 125.0f));
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 8.0f);
			ImGui::Text(w_Prop.Title.c_str());

			ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.0f);
			ImGui::SameLine(ImGui::GetWindowWidth() - 45.f);

			if (ImGui::ImageButton("EXIE", (ImTextureRef)textureBar.GetID(), ImVec2(20.f, 20.f), ImVec2(0, 0), ImVec2(0.3333f, 1.0f)))
			{
				// Close The Application
				*pRunning = false;
			}

			ImGui::SameLine(ImGui::GetWindowWidth() - 84.f);
			if (ImGui::ImageButton("MAXMIZE", (ImTextureRef)textureBar.GetID(), ImVec2(20.f, 20.f), ImVec2(0.3333f, 0.0f), ImVec2(0.6666f, 1.0f)))
			{
				static bool max = false;
				if (!max)
				{
					SetWin32Show(w_Window, SW_MAXIMIZE);
					max = true;
				}
				else
				{
					SetWin32Show(w_Window, SW_SHOWDEFAULT);
					max = false;
				}
			}

			ImGui::SameLine(ImGui::GetWindowWidth() - 124.f);
			if (ImGui::ImageButton("MIXMIZE", (ImTextureRef)textureBar.GetID(), ImVec2(20.f, 20.f), ImVec2(0.6666f, 0.0f), ImVec2(1.0f, 1.0f)))
			{
				SetWin32Show(w_Window, SW_MINIMIZE);
			}

		}
		ImGui::EndMainMenuBar();
		ImGui::PopStyleVar();

		if (ImGui::Begin("Editor Style"))
			ImGui::ShowStyleEditor();
		ImGui::End();

	}

	void WindowsWindow::ProcessChangesForWIN32()
	{
		SDL_PropertiesID props = SDL_GetWindowProperties(w_Window);

		HWND hwnd = (HWND)SDL_GetPointerProperty(
			props,
			SDL_PROP_WINDOW_WIN32_HWND_POINTER,
			NULL
		);

		ED_ASSERT(hwnd, "Failed to take HWND WIN32 for SDL3 window");

		LONG style = GetWindowLong(hwnd, GWL_STYLE);

		style &= ~(WS_CAPTION | WS_THICKFRAME);
		style &= ~WS_SYSMENU;
		style &= ~WS_MAXIMIZEBOX;
		style &= ~WS_MINIMIZEBOX;

		SetWindowLong(hwnd, GWL_STYLE, style);


		// TitleBar Color
		DWORD border = RGB(100, 100, 100);
		DwmSetWindowAttribute(hwnd, DWMWA_BORDER_COLOR, &border, sizeof(border));

		MARGINS margins = { 1, 1, 1, 1 };
		DwmExtendFrameIntoClientArea(hwnd, &margins);

		DWM_WINDOW_CORNER_PREFERENCE cornerPreference = DWMWCP_ROUND;
		DwmSetWindowAttribute(hwnd, DWMWA_WINDOW_CORNER_PREFERENCE, &cornerPreference, sizeof(cornerPreference));

		SetWindowPos(
			hwnd, NULL,
			0, 0, 0, 0,
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED
		);

		// Update window's size for fixe some ui components
		SDL_SetWindowSize(w_Window, w_Prop.Width - 40, w_Prop.Height - 20);
		SDL_SetWindowSize(w_Window, w_Prop.Width, w_Prop.Height);
	}

	WindowsWindow* CreateWindowsWindow()
	{
		return new WindowsWindow();
	}

	

}

#endif