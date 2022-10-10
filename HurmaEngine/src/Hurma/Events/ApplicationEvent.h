#pragma once
#include "Event.h"

namespace Hurma {

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: mWidth(width), mHeight(height) {}

		unsigned int getWidth() const { return mWidth; }
		unsigned int getHeight() const { return mHeight; }

		std::string toString() const override
		{
			return getName();
		}

		DECLARE_EVENT_TYPE(WindowResize)
		DECLARE_EVENT_CATEGORY(EventCategoryApplication)
	private:
		unsigned int mWidth, mHeight;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		DECLARE_EVENT_TYPE(WindowClose)
		DECLARE_EVENT_CATEGORY(EventCategoryApplication)
	};

	class AppTickEvent : public Event
	{
	public:
		AppTickEvent() = default;

		DECLARE_EVENT_TYPE(AppTick)
		DECLARE_EVENT_CATEGORY(EventCategoryApplication)
	};

	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;

		DECLARE_EVENT_TYPE(AppUpdate)
		DECLARE_EVENT_CATEGORY(EventCategoryApplication)
	};

	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;

		DECLARE_EVENT_TYPE(AppRender)
		DECLARE_EVENT_CATEGORY(EventCategoryApplication)
	};
}