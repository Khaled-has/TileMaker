#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <string>

#include "Core/Events/Event.h"

namespace Editor {


	struct WindowProp
	{
		WindowProp(std::string title = "TileMaker", 
			unsigned int width = 1440, 
			unsigned int height = 720
		)
			: Title(title), Width(width), Height(height)
		{
		}

		std::string Title;
		unsigned int Width;
		unsigned int Height;
	};

	class Window
	{
	public:
		using EventFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void OnUpdate() = 0;
		virtual void OnEvent(EventFn evenFn) const = 0;
		virtual void Create() = 0;
		virtual void CustomBar() = 0;

		virtual WindowProp GetProperties() const = 0;

		virtual void* GetNativeWindow() const = 0;
		virtual void* GetNativeContext() const = 0;

	};

}

#endif