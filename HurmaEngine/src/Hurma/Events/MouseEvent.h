#pragma once
#include <string>
#include "Event.h"
#include "../MouseCode.h"

namespace Hurma
{

    class MouseMovedEvent : public Event
	{
	 public:
		MouseMovedEvent(const float x, const float y)
			: mMouseX(x), mMouseY(y) {}

		float getX() const { return mMouseX; }
		float getY() const { return mMouseY; }

		std::string toString() const override
		{
			return getName();
		}

		DECLARE_EVENT_TYPE(MouseMoved)
		DECLARE_EVENT_CATEGORY(EventCategoryMouse | EventCategoryInput)

	 private:
		float mMouseX, mMouseY;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(const float xOffset, const float yOffset)
			: mXOffset(xOffset), mYOffset(yOffset) {}

		float getXOffset() const { return mXOffset; }
		float getYOffset() const { return mYOffset; }

		std::string toString() const override
		{
			return getName();
		}

		DECLARE_EVENT_TYPE(MouseScrolled)
		DECLARE_EVENT_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float mXOffset, mYOffset;
	};

	class MouseButtonEvent : public Event
	{
	public:
		MouseCode getMouseButton() const { return mButton; }

		DECLARE_EVENT_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)

	protected:
		MouseButtonEvent(MouseCode button)
			: mButton(button) {}

		MouseCode mButton;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(MouseCode button)
			: MouseButtonEvent(button) {}

		std::string toString() const override
		{
			return getName();
		}

		DECLARE_EVENT_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(MouseCode button)
			: MouseButtonEvent(button) {}

		std::string toString() const override
		{
			return getName();
		}

		DECLARE_EVENT_TYPE(MouseButtonReleased)
	};

}