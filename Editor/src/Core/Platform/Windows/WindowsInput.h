#ifndef WINDOWSINPIT_H
#define WINDOWSINPIT_H

#ifdef WIN32

#include "Core/Events/Input.h"

namespace Editor {

    class WindowsInput : public Input
    {
    protected:
        virtual bool IsKeyPressedImpl(unsigned int keycode) override;

        virtual bool IsMouseButtonPressedImpl(unsigned int button) override;
        virtual std::pair<float, float> GetMousePositionImpl() override;
    };

}

#endif  // WIN32

#endif