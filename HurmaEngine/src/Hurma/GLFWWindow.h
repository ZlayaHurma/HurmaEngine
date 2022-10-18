#pragma once
#include "Hurma/IWindow.h"

struct GLFWwindow;

namespace Hurma
{
    class GLFWWindow : public IWindow
    {
        
     public:

        GLFWWindow(const WindowProps& props);

        void onUpdate() override;

        uint32_t getWidth() const override;

        uint32_t getHeight() const override;

        void setEventCallback(const EventCallbackFn& callback) override { mWindowData.callback = callback; }

        void setVSync(bool enabled) override;

        bool isVSync() const override;

        void* getNativeWindow() const override;

        bool shouldClose() const override;

       private:

        struct GLFWWindowData
        {
            uint32_t width{};
            uint32_t height{};
            EventCallbackFn callback{};
            bool isVSync{};
        } mWindowData;

        GLFWwindow* mWindow;
    };

}
