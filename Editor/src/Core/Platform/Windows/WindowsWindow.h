#ifndef WINDOWSWINDOW_H
#define WINDOWSWINDOW_H

#ifdef WIN32

#include "Core/Platform/Window.h"

#include <glad/glad.h>
#include <SDL3/SDL.h>

#include "Core/Events/KeyEvent.h"
#include "Core/Events/ApplicationEvent.h"
#include "Core/Events/MouseEvent.h"

namespace Editor
{

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow();
		~WindowsWindow();

		void OnUpdate() override;
		void OnEvent(EventFn evenFn) const override;
		void Create() override;

		unsigned int GetWidth() const override { return w_Prop.Width; }
		unsigned int GetHeight() const override { return w_Prop.Height; }

		inline virtual WindowProp GetProperties() const { return w_Prop; }

		inline virtual void* GetNativeWindow() const override { return w_Window; }
		inline virtual void* GetNativeContext() const override { return w_Context; }

	private:
		WindowProp w_Prop{"TileMaker  ( Release 1.0.0v )"};

		SDL_Window* w_Window	= nullptr;
		SDL_GLContext w_Context = 0;
	};

	WindowsWindow* CreateWindowsWindow();

}

#endif	// WIN32


#endif