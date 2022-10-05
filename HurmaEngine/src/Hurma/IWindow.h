#pragma once
#include <stdint.h>
#include <functional>
#include "Hurma/Events/Event.h"

namespace Hurma
{

    class IWindow
	{
	public:
		using EventCallbackFn = std::function<void(const Event&)>;

		virtual ~IWindow() = default;

		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;
	};

    struct WindowProps
    {
        size_t windowWidth{};
        size_t windowHeight{};
        std::string title{};
    };

}
