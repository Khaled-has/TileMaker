#include "WindowsInput.h"

#include <SDL3/SDL.h>
#include "Application.h"

namespace Editor {

#ifdef WIN32
	Input* Input::s_Instance = new WindowsInput();
#endif

	bool WindowsInput::IsKeyPressedImpl(unsigned int keycode)
	{
		SDL_Scancode scan = SDL_GetScancodeFromKey(keycode, SDL_KMOD_NONE);
		const bool* state = SDL_GetKeyboardState(NULL);

		return state[scan];
	}

	bool WindowsInput::IsMouseButtonPressedImpl(unsigned int button)
	{
		Uint32 mask = SDL_GetMouseState(NULL, NULL);
		return (mask & static_cast<Uint32>(button));
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		float x, y;
		SDL_GetMouseState(&x, &y);

		return { x, y };
	}

}