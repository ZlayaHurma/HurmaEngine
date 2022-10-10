#pragma once
#include <stdint.h>
#include <functional>

namespace Hurma
{
    class Event;

    class IWindow
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~IWindow() = default;

		virtual void onUpdate() = 0;

		virtual uint32_t getWidth() const = 0;
		virtual uint32_t getHeight() const = 0;

		// Window attributes
		virtual void setEventCallback(const EventCallbackFn& callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		virtual void* getNativeWindow() const = 0;
	};

    struct WindowProps
    {
        uint32_t windowWidth{};
        uint32_t windowHeight{};
        std::string title{};
    };

}
