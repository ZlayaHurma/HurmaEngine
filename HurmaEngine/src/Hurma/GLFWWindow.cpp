#include "GLFWWindow.h"
#include "Hurma/Events/KeyEvent.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"

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

       mWindowData.width = props.windowWidth;
       mWindowData.height = props.windowHeight;

       setVSync(true);

       glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height)
		{
			GLFWWindowData* data = reinterpret_cast<GLFWWindowData*>(glfwGetWindowUserPointer(window));
			data->width = width;
			data->height = height;

			WindowResizeEvent event(width, height);
			data->callback(event);
		});

		glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* window)
		{
			GLFWWindowData* data = reinterpret_cast<GLFWWindowData*>(glfwGetWindowUserPointer(window));
			WindowCloseEvent event;
			data->callback(event);
		});

		glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			GLFWWindowData* data = reinterpret_cast<GLFWWindowData*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data->callback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data->callback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, true);
					data->callback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(mWindow, [](GLFWwindow* window, unsigned int keycode)
		{
			GLFWWindowData* data = reinterpret_cast<GLFWWindowData*>(glfwGetWindowUserPointer(window));

			KeyTypedEvent event(keycode);
			data->callback(event);
		});

		glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int mods)
		{
			GLFWWindowData* data = reinterpret_cast<GLFWWindowData*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data->callback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data->callback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			GLFWWindowData* data = reinterpret_cast<GLFWWindowData*>(glfwGetWindowUserPointer(window));

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data->callback(event);
		});

		glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double xPos, double yPos)
		{
			GLFWWindowData* data = reinterpret_cast<GLFWWindowData*>(glfwGetWindowUserPointer(window));

			MouseMovedEvent event((float)xPos, (float)yPos);
			data->callback(event);
		});
    }
    
    void GLFWWindow::onUpdate() 
    {
        glfwPollEvents();
        glfwSwapBuffers(mWindow);
    }
    
    uint32_t GLFWWindow::getWidth() const {
        return mWindowData.width;
    }
    
    uint32_t GLFWWindow::getHeight() const {
        return mWindowData.height;
    }
    
    void GLFWWindow::setVSync(bool enabled) 
    {
        if(enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        mWindowData.isVSync = enabled;
    }
    
    bool GLFWWindow::isVSync() const 
    {
        return mWindowData.isVSync;
    }
    
    void* GLFWWindow::getNativeWindow() const 
    {
        return mWindow;
    }

}
