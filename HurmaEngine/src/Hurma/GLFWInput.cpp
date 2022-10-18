#include "GLFWInput.h"
#include "GLFW/glfw3.h"
#include "Application.h"
#include "IWindow.h"

namespace Hurma
{
    int hurmaKeyCodeToGLWFKeyCode(KeyCode keyCode)
    {
        switch(keyCode)
        { 
            case KeyCode::Left:
                return GLFW_KEY_LEFT;
            case KeyCode::Right:
                return GLFW_KEY_RIGHT;
            case KeyCode::Up:
                return GLFW_KEY_UP;
            case KeyCode::Down:
                return GLFW_KEY_DOWN;
        }

        return GLFW_KEY_UNKNOWN;
    }

    int hurmaMouseToGLWFMouse(MouseCode mouse)
    {
        switch(mouse)
        { 
            case MouseCode::Left:
                return GLFW_MOUSE_BUTTON_1;
            case MouseCode::Right:
                return GLFW_MOUSE_BUTTON_2;
        }

        return -1;
    }
    
    bool GLFWInput::isKeyPressedImpl(KeyCode keyCode) 
    {
        auto* window = reinterpret_cast<GLFWwindow*>(Application::get().getWindow()->getNativeWindow());
		auto state = glfwGetKey(window, hurmaKeyCodeToGLWFKeyCode(keyCode));
		return state == GLFW_PRESS;
    }

    bool GLFWInput::isMouseButtonPressedImpl(const MouseCode button)
	{
		auto* window = reinterpret_cast<GLFWwindow*>(Application::get().getWindow()->getNativeWindow());
		auto state = glfwGetMouseButton(window, hurmaMouseToGLWFMouse(button));
		return state == GLFW_PRESS;
	}

	glm::vec2 GLFWInput::getMousePositionImpl()
	{
		auto* window = reinterpret_cast<GLFWwindow*>(Application::get().getWindow()->getNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float GLFWInput::getMouseXImpl()
	{
		return getMousePosition().x;
	}

	float GLFWInput::getMouseYImpl()
	{
		return getMousePosition().y;
	}

}