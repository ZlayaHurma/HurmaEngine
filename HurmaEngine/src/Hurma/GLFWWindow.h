#pragma once
#include "Hurma/IWindow.h"
#include "GLFW/glfw3.h"

namespace Hurma
{

    class GLFWWindow : public IWindow
    {
        
     public:

        GLFWWindow(const WindowProps& props);

        void OnUpdate() override;

        uint32_t GetWidth() const override;

        uint32_t GetHeight() const override;

        void SetEventCallback(const EventCallbackFn& callback) override { mWindowData.callback = callback; }

        void SetVSync(bool enabled) override;

        bool IsVSync() const override;

        void* GetNativeWindow() const override;

     private:

        struct GLWindowData
        {
            size_t width{};
            size_t height{};
            EventCallbackFn callback{};
        } mWindowData;

        GLFWwindow* mWindow;

    };

}
