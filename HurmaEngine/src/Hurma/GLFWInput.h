#pragma once
#include "Input.h"

namespace Hurma
{
    class HURMA_API GLFWInput : public Input
    {
    private:
        bool isKeyPressedImpl(KeyCode keyCode) override;

        bool isMouseButtonPressedImpl(MouseCode button) override;

        glm::vec2 getMousePositionImpl() override;

        float getMouseXImpl() override;

        float getMouseYImpl() override;
    };

}  // namespace Hurma