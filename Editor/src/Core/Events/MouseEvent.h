#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include "Event.h"

namespace Editor {

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float mouseX, float mouseY)
			: m_PosX(mouseX), m_PosY(mouseY)
		{
		}

		inline float GetPosX() const { return m_PosX; }
		inline float GetPosY() const { return m_PosY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse Moved: " << m_PosX << ", " << m_PosY;
			return ss.str();
		}

		SET_EVENT_TYPE(MouseCategoryEvents)
		SET_CLASS_TYPE(MouseMoved)
	private:
		float m_PosX, m_PosY;
	};

	class MousePressedEvent : public Event
	{
	public:
		MousePressedEvent(unsigned int buttonCode)
			: buttonCode(buttonCode)
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse Pressed: " << Event::e_Handle;
			return ss.str();
		}

		inline unsigned int GetButtonCode() const { return buttonCode; }

		SET_EVENT_TYPE(MouseCategoryEvents)
		SET_CLASS_TYPE(MousePressed)
	private:
		unsigned int buttonCode;
	};

	class MouseReleasedEvent : public Event
	{
	public:
		MouseReleasedEvent(unsigned int buttonCode)
			: buttonCode(buttonCode)
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse Released: " << Event::e_Handle;
			return ss.str();
		}

		inline unsigned int GetButtonCode() const { return buttonCode; }

		SET_EVENT_TYPE(MouseCategoryEvents)
		SET_CLASS_TYPE(MouseReleased)
	private:
		unsigned int buttonCode;
	};

	class MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(float xOff, float yOff)
		 :	xOffset(xOff), yOffset(yOff)
		{
		}

		inline float GetXOffset() const { return xOffset; }
		inline float GetYOffset() const { return yOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse Scroll Offset: " << xOffset << ", " << yOffset;
			return ss.str();
		}

		SET_EVENT_TYPE(MouseCategoryEvents)
		SET_CLASS_TYPE(MouseScroll)
	private:
		float xOffset, yOffset;
	};

}

#define ED_BUTTON_LEFT     1
#define ED_BUTTON_MIDDLE   2
#define ED_BUTTON_RIGHT    3
#define ED_BUTTON_X1       4
#define ED_BUTTON_X2       5

#endif