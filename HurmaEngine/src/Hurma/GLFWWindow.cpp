#include "GLFWWindow.h"
#include "Hurma/Events/KeyEvent.h"

namespace Hurma
{

    GLFWWindow::GLFWWindow(const WindowProps& props) 
    {
        
       mWindow = glfwCreateWindow((int)props.windowWidth, (int)props.windowHeight, props.title.c_str(), nullptr, nullptr);
       glfwSetWindowUserPointer(mWindow, &mWindowData);

       glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height)
	   {
	       GLWindowData* data = reinterpret_cast<GLWindowData*>(glfwGetWindowUserPointer(window));
	       data->width = width;
	       data->height = height;
           
	       KeyPressedEvent event(0, false);
	       data->callback(event);
	   });
    }
    
    void GLFWWindow::OnUpdate() {
    }
    
    uint32_t GLFWWindow::GetWidth() const {
        return mWindowData.width;
    }
    
    uint32_t GLFWWindow::GetHeight() const {
        return mWindowData.height;
    }
    
    void GLFWWindow::SetVSync(bool enabled) {
    }
    
    bool GLFWWindow::IsVSync() const {
        return false;
    }
    
    void* GLFWWindow::GetNativeWindow() const {
        return mWindow;
    }

}
