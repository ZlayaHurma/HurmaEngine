#pragma once

#include "Hurma/Core.h"
#include <string>
#include <functional>

namespace Hurma
{

    enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication    = BIT(0),
		EventCategoryInput          = BIT(1),
		EventCategoryKeyboard       = BIT(2),
		EventCategoryMouse          = BIT(3),
		EventCategoryMouseButton    = BIT(4)
	};

    class Event 
    {

        friend class EventDispatcher;

     protected:
        Event() = default;

     public:
        virtual EventType getType() const = 0;
        virtual std::string getName() const = 0;
        virtual std::string toString() const { return getName(); }
        virtual int getCategoryFlags() const = 0;
    
        bool isInCategory(EventCategory category) const
		{
			return getCategoryFlags() & category;
		}

        bool isHandled() { return handled; }

     private:
        bool handled {false};
    };

    #define DECLARE_EVENT_TYPE(type) static EventType getStaticType() { return EventType::type; }\
								virtual EventType getType() const override { return getStaticType(); }\
								virtual std::string getName() const override { return #type; }

    #define DECLARE_EVENT_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

    template <class T>
    concept EventBased = std::derived_from<T, Event>;

    class EventDispatcher {
     public:
        EventDispatcher(Event& event) 
            : mEvent(event)
        {}

        template<EventBased EventType>
        bool dispatch(std::function<bool(EventType&)> eventFunc)
        {
            if(EventType::getStaticType() != mEvent.getType())
                return false;

            mEvent.handled |= eventFunc(dynamic_cast<EventType&>(mEvent));
            return true;
        }

      private:
        Event& mEvent;
    };

}