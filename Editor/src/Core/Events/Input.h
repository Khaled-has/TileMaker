#ifndef INPUT_H
#define INPUT_H

#include "KeyEvent.h"
#include "MouseEvent.h"

namespace Editor {

    class Input
    {
    public:

        inline static bool IsKeyPressed(unsigned int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }

        inline static bool IsMouseButtonPressed(unsigned int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
        inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
        inline static float GetMouseX() { return s_Instance->GetMousePositionImpl().first; }
        inline static float GetMouseY() { return s_Instance->GetMousePositionImpl().second; }
    protected:
        virtual bool IsKeyPressedImpl(unsigned int keycode) = 0;

        virtual bool IsMouseButtonPressedImpl(unsigned int button) = 0;
        virtual std::pair<float, float> GetMousePositionImpl() = 0;
    private:
        static Input* s_Instance;
    };
    
}

#endif