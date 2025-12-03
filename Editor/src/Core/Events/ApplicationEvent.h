#ifndef APPLICATIONEVENT_H
#define APPLICATIONEVENT_H

#include "pch.h"
#include "Event.h"

#define ED_APP_QUIT 1

namespace Editor {

	class ApplicationEvent : public Event
	{
	public:
		ApplicationEvent(unsigned int appcode)
			: appCode(appcode)
		{
		}

		inline unsigned int GetAppCode() const { return appCode; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Application: " << appCode;
			return ss.str();
		}

		SET_EVENT_TYPE(ApplicationCategoryEvents)
		SET_CLASS_TYPE(WindowApp)
	private:
		unsigned int appCode;
	};

}

#endif