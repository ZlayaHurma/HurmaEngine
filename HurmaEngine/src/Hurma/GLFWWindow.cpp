#include "GLFWWindow.h"
#include "Hurma/Events/KeyEvent.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Hurma
{

    GLFWWindow::GLFWWindow(const WindowProps& props) 
    {
       int success = glfwInit();
       _ASSERTE(success);

       mWindow = glfwCreateWindow((int)props.windowWidth, (int)props.windowHeight, props.title.c_str(), nullptr, nullptr);
       glfwSetWindowUserPointer(mWindow, &mWindowData);
       glfwMakeContextCurrent(mWindow);

       int gladSuccess = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
       _ASSERTE(gladSuccess);

       glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height)
	   {
	       GLWindowData* data = reinterpret_cast<GLWindowData*>(glfwGetWindowUserPointer(window));
	       data->width = width;
	       data->height = height;
           
	       KeyPressedEvent event(0, false);
	       data->callback(event);
	   });
    }
    
    void GLFWWindow::onUpdate() {
        glfwPollEvents();
        glfwSwapBuffers(mWindow);
    }
    
    uint32_t GLFWWindow::getWidth() const {
        return mWindowData.width;
    }
    
    uint32_t GLFWWindow::getHeight() const {
        return mWindowData.height;
    }
    
    void GLFWWindow::setVSync(bool enabled) {
    }
    
    bool GLFWWindow::isVSync() const {
        return false;
    }
    
    void* GLFWWindow::getNativeWindow() const {
        return mWindow;
    }

}
