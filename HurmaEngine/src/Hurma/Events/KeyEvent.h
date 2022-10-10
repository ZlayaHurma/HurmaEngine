#pragma once
#include "Event.h"

namespace Hurma
{
    class KeyEvent : public Event 
    {
     public:
        KeyEvent(int keyCode) 
            : mKeyCode(keyCode)
        {}

        DECLARE_EVENT_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

        int getKeyCode() { return mKeyCode; }

     private:
         int mKeyCode;
    };

    class KeyPressedEvent : public KeyEvent 
    {
     public:
        KeyPressedEvent(int keyCode, bool isRepeated) 
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
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string toString() const override
		{
			return getName();
		}

		DECLARE_EVENT_TYPE(KeyReleased)
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string toString() const override
		{
			return getName();
		}

		DECLARE_EVENT_TYPE(KeyTyped)
	};
}