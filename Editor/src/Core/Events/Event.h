#ifndef EVENT_H
#define EVENT_H

#include "hzpch.h"

enum class EventClassType
{
	None = 0,
	KeyPressed, KeyReleased,
	MouseMoved, MousePressed, MouseReleased, MouseScroll,
	WindowApp
};

enum EventType
{
	None						= 0,
	MouseCategoryEvents			= BIT(1),
	KeyboardCategoryEvents		= BIT(2),
	ApplicationCategoryEvents	= BIT(3)
};



#define SET_EVENT_TYPE(type) virtual EventType GetType() const override { return EventType::##type; }\
							 virtual const char* GetName() const override { return #type; }
#define SET_CLASS_TYPE(type) virtual EventClassType GetEventClassType() const override { return EventClassType::##type; }

#define EVENT_CHECK(x, y) { if ((x & EventType) == x) return true; else return false; }

namespace Editor {

	class Event
	{
	public:
		Event() { e_Handle = 0; }

		virtual EventType GetType() const = 0;
		virtual EventClassType GetEventClassType() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const = 0;

		inline unsigned int GetHandle() const { return e_Handle; }
		inline Event& GetEvent() { return *this; }

	protected:
		unsigned int e_Handle;
	};


	inline bool Dispatch(Event& ev_1, Event& ev_2)
	{
		return (ev_1.GetHandle() == ev_2.GetHandle() && ev_1.GetType() == ev_2.GetType() && ev_1.GetEventClassType() == ev_2.GetEventClassType()) ? true : false;
	}

}


#endif