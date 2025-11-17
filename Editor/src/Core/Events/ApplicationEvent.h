#ifndef APPLICATIONEVENT_H
#define APPLICATIONEVENT_H

#include "hzpch.h"
#include "Event.h"

#define ED_APP_QUIT 1

namespace Editor {

	class ApplicationEvent : public Event
	{
	public:
		ApplicationEvent(unsigned int keycode)
		{
			e_Handle = keycode;
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Application: " << Event::e_Handle;
			return ss.str();
		}

		SET_EVENT_TYPE(ApplicationCategoryEvents)
		SET_CLASS_TYPE(WindowApp)
	};

}

#endif