#ifndef EVENT_H
#define EVENT_H

#include "pch.h"

namespace Editor {

	enum class EventType
	{
		None = 0,
		KeyPressed, KeyReleased, KeyTyped,
		MouseMoved, MousePressed, MouseReleased, MouseScroll,
		WindowApp
	};

	enum EventCategory
	{
		None						= 0,
		MouseCategoryEvents			= BIT(1),
		KeyboardCategoryEvents		= BIT(2),
		ApplicationCategoryEvents	= BIT(3)
	};



#define SET_EVENT_TYPE(type) virtual const char* GetName() const override { return #type; }
							 

#define SET_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
							 virtual EventType GetType() const override { return GetStaticType(); }

	class Event
	{
		friend class EventDispatcher;
	public:
		Event() 
			: e_Handle(true)
		{
		}

		virtual EventType GetType() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const = 0;

		bool e_Handle;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		template<typename T>
		bool Dispatcher(EventFn<T> func)
		{
			if (m_Event.GetType() == T::GetStaticType()/* && m_Event.e_Handle*/)
			{
				m_Event.e_Handle = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

}


#endif