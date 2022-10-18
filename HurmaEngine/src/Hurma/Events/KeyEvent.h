#pragma once
#include "Event.h"
#include "../KeyCode.h"

namespace Hurma
{
    class KeyEvent : public Event 
    {
     public:
        KeyEvent(KeyCode keyCode) 
            : mKeyCode(keyCode)
        {}

        DECLARE_EVENT_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

        KeyCode getKeyCode() { return mKeyCode; }

     private:
         KeyCode mKeyCode;
    };

    class KeyPressedEvent : public KeyEvent 
    {
     public:
        KeyPressedEvent(KeyCode keyCode, bool isRepeated) 
        : KeyEvent(keyCode)
        , mIsRepeated(isRepeated)
        {}

        DECLARE_EVENT_TYPE(KeyPressed)

        bool isRepeated() { return mIsRepeated; }

     private:
         bool mIsRepeated;
    };

    class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(KeyCode keyCode)
			: KeyEvent(keyCode) {}

		std::string toString() const override
		{
			return getName();
		}

		DECLARE_EVENT_TYPE(KeyReleased)
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(KeyCode keyCode)
			: KeyEvent(keyCode) {}

		std::string toString() const override
		{
			return getName();
		}

		DECLARE_EVENT_TYPE(KeyTyped)
	};
}