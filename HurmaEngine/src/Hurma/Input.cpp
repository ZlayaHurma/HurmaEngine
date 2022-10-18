#include "Input.h"
#include "GLFWInput.h"

namespace Hurma
{
    Input* Input::mInputInstance = new GLFWInput();
}