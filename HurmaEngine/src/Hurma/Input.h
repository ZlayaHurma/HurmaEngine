#pragma once
#include "Core.h"
#include "KeyCode.h"
#include "MouseCode.h"
#include "glm/ext/vector_float2.hpp"

namespace Hurma
{
    class HURMA_API Input
    {
    public:
        static bool isKeyPressed(KeyCode keyCode) { return mInputInstance->isKeyPressedImpl(keyCode); }
        static bool isMouseButtonPressed(MouseCode button) { return mInputInstance->isMouseButtonPressedImpl(button); }
        static glm::vec2 getMousePosition() { return mInputInstance->getMousePositionImpl(); }
		static float getMouseX() { return mInputInstance->getMouseXImpl(); }
		static float getMouseY() { return mInputInstance->getMouseYImpl(); }

    private:
        virtual bool isKeyPressedImpl(KeyCode keyCode) = 0;
        virtual bool isMouseButtonPressedImpl(MouseCode button) = 0;
        virtual glm::vec2 getMousePositionImpl() = 0;
		virtual float getMouseXImpl() = 0;
		virtual float getMouseYImpl() = 0;

    private:
        static Input* mInputInstance;
    };
}