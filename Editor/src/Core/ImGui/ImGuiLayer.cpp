#include "ImGuiLayer.h"

#include <imgui.h>
#include <imgui_impl_opengl3.h>

#include <SDL3/SDL.h>

namespace Editor {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		// --- ImGui Init ---
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		
		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		(void)io;

		io.Fonts->AddFontFromFileTTF((std::string(ASSETS_PATH) + "Fonts/JetBrainsMono-Bold.ttf").c_str());

		ImGui::StyleColorsDark();
		
		ImGui_ImplOpenGL3_Init("#version 460");
		
		ED_LOG_WARN("||---> ImGui Initialized <---||");
	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(1440, 720);
		
		static bool first = true;
		static double last = 0;
		static double current;
		if (first)
		{
			last = SDL_GetPerformanceCounter();
			first = false;
		}
		current = SDL_GetPerformanceCounter();
		double deltaTime = (current - last) / SDL_GetPerformanceFrequency();
		last = current;

		io.DeltaTime = (float)deltaTime;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
		
		static bool show;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event)
	{

		EventDispatcher dispatcher(event);

		// Key Pressed Event
		dispatcher.Dispatcher<KeyPressedEvent>(BIND_FN(ImGuiLayer::OnKeyPressedEvent));

		// Key Released Event
		dispatcher.Dispatcher<KeyReleasedEvent>(BIND_FN(ImGuiLayer::OnKeyReleasedEvent));

		// Key Typed Event
		dispatcher.Dispatcher<KeyTypedEvent>(BIND_FN(ImGuiLayer::OnKeyTypedEvent));

		// Mouse Moved Event
		dispatcher.Dispatcher<MouseMovedEvent>(BIND_FN(ImGuiLayer::OnMouseMovedEvent));

		// Mouse Pressed Event
		dispatcher.Dispatcher<MousePressedEvent>(BIND_FN(ImGuiLayer::OnMousePressedEvent));

		// Mouse Released Event
		dispatcher.Dispatcher<MouseReleasedEvent>(BIND_FN(ImGuiLayer::OnMouseReleasedEvent));

		// Mouse Scroll Event
		dispatcher.Dispatcher<MouseScrollEvent>(BIND_FN(ImGuiLayer::OnMouseScrollEvent));

	}

	ImGuiKey ConvertKeys(unsigned int keycode)
	{
		switch (keycode)
		{
		case ED_TAB: return ImGuiKey_Tab;
		case ED_LEFT: return ImGuiKey_LeftArrow;
		case ED_RIGHT: return ImGuiKey_RightArrow;
		case ED_UP: return ImGuiKey_UpArrow;
		case ED_DOWN: return ImGuiKey_DownArrow;
		case ED_PAGEUP: return ImGuiKey_PageUp;
		case ED_PAGEDOWN: return ImGuiKey_PageDown;
		case ED_HOME: return ImGuiKey_Home;
		case ED_END: return ImGuiKey_End;
		case ED_INSERT: return ImGuiKey_Insert;
		case ED_DELETE: return ImGuiKey_Delete;
		case ED_BACKSPACE: return ImGuiKey_Backspace;
		case ED_SPACE: return ImGuiKey_Space;
		case ED_RETURN: return ImGuiKey_Enter;
		case ED_ESCAPE: return ImGuiKey_Escape;
		case ED_COMMA: return ImGuiKey_Comma;
		case ED_PERIOD: return ImGuiKey_Period;
		case ED_SEMICOLON: return ImGuiKey_Semicolon;
		case ED_CAPSLOCK: return ImGuiKey_CapsLock;
		case ED_SCROLLLOCK: return ImGuiKey_ScrollLock;
		case ED_NUMLOCKCLEAR: return ImGuiKey_NumLock;
		case ED_PRINTSCREEN: return ImGuiKey_PrintScreen;
		case ED_PAUSE: return ImGuiKey_Pause;
		case ED_LCTRL: return ImGuiKey_LeftCtrl;
		case ED_LSHIFT: return ImGuiKey_LeftShift;
		case ED_LALT: return ImGuiKey_LeftAlt;
		case ED_LGUI: return ImGuiKey_LeftSuper;
		case ED_RCTRL: return ImGuiKey_RightCtrl;
		case ED_RSHIFT: return ImGuiKey_RightShift;
		case ED_RALT: return ImGuiKey_RightAlt;
		case ED_RGUI: return ImGuiKey_RightSuper;
		case ED_APPLICATION: return ImGuiKey_Menu;
		case ED_0: return ImGuiKey_0;
		case ED_1: return ImGuiKey_1;
		case ED_2: return ImGuiKey_2;
		case ED_3: return ImGuiKey_3;
		case ED_4: return ImGuiKey_4;
		case ED_5: return ImGuiKey_5;
		case ED_6: return ImGuiKey_6;
		case ED_7: return ImGuiKey_7;
		case ED_8: return ImGuiKey_8;
		case ED_9: return ImGuiKey_9;
		case ED_A: return ImGuiKey_A;
		case ED_B: return ImGuiKey_B;
		case ED_C: return ImGuiKey_C;
		case ED_D: return ImGuiKey_D;
		case ED_E: return ImGuiKey_E;
		case ED_F: return ImGuiKey_F;
		case ED_G: return ImGuiKey_G;
		case ED_H: return ImGuiKey_H;
		case ED_I: return ImGuiKey_I;
		case ED_J: return ImGuiKey_J;
		case ED_K: return ImGuiKey_K;
		case ED_L: return ImGuiKey_L;
		case ED_M: return ImGuiKey_M;
		case ED_N: return ImGuiKey_N;
		case ED_O: return ImGuiKey_O;
		case ED_P: return ImGuiKey_P;
		case ED_Q: return ImGuiKey_Q;
		case ED_R: return ImGuiKey_R;
		case ED_S: return ImGuiKey_S;
		case ED_T: return ImGuiKey_T;
		case ED_U: return ImGuiKey_U;
		case ED_V: return ImGuiKey_V;
		case ED_W: return ImGuiKey_W;
		case ED_X: return ImGuiKey_X;
		case ED_Y: return ImGuiKey_Y;
		case ED_Z: return ImGuiKey_Z;
		case ED_F1: return ImGuiKey_F1;
		case ED_F2: return ImGuiKey_F2;
		case ED_F3: return ImGuiKey_F3;
		case ED_F4: return ImGuiKey_F4;
		case ED_F5: return ImGuiKey_F5;
		case ED_F6: return ImGuiKey_F6;
		case ED_F7: return ImGuiKey_F7;
		case ED_F8: return ImGuiKey_F8;
		case ED_F9: return ImGuiKey_F9;
		case ED_F10: return ImGuiKey_F10;
		case ED_F11: return ImGuiKey_F11;
		case ED_F12: return ImGuiKey_F12;
		case ED_F13: return ImGuiKey_F13;
		case ED_F14: return ImGuiKey_F14;
		case ED_F15: return ImGuiKey_F15;
		case ED_F16: return ImGuiKey_F16;
		case ED_F17: return ImGuiKey_F17;
		case ED_F18: return ImGuiKey_F18;
		case ED_F19: return ImGuiKey_F19;
		case ED_F20: return ImGuiKey_F20;
		case ED_F21: return ImGuiKey_F21;
		case ED_F22: return ImGuiKey_F22;
		case ED_F23: return ImGuiKey_F23;
		case ED_F24: return ImGuiKey_F24;
		case ED_AC_BACK: return ImGuiKey_AppBack;
		case ED_AC_FORWARD: return ImGuiKey_AppForward;
		default: return ImGuiKey_None;
		}
	}

	unsigned int ConvertButtons(unsigned int buttoncode)
	{
		switch (buttoncode)
		{
		case ED_BUTTON_LEFT: return 0;
			break;
		case ED_BUTTON_RIGHT: return 1;
			break;
		case ED_BUTTON_MIDDLE: return 2;
			break;
		case ED_BUTTON_X1: return 3;
			break;
		case ED_BUTTON_X2: return 4;
			break;
		default: return 0;
		}
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		unsigned int k = e.GetKeyCode();

		io.KeyCtrl  = (k == ED_LCTRL || k == ED_RCTRL)		?	true : false;
		io.KeyShift = (k == ED_LSHIFT || k == ED_RSHIFT)	?	true : false;
		io.KeyAlt   = (k == ED_LALT || k == ED_RALT)		?	true : false;

		io.AddKeyEvent(ConvertKeys(k), true);

		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddKeyEvent(ConvertKeys(e.GetKeyCode()), false);

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();

		if (e.GetKeyCode() > 0 && e.GetKeyCode() < 0x10000)
			io.AddInputCharacter((unsigned short)e.GetKeyCode());

		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMousePosEvent(e.GetPosX(), e.GetPosY());

		return true;
	}

	bool ImGuiLayer::OnMousePressedEvent(MousePressedEvent& e)
	{

		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(ConvertButtons(e.GetButtonCode()), true);

		return false;
	}

	bool ImGuiLayer::OnMouseReleasedEvent(MouseReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(ConvertButtons(e.GetButtonCode()), false);

		return false;
	}

	bool ImGuiLayer::OnMouseScrollEvent(MouseScrollEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseWheelEvent(e.GetYOffset(), e.GetXOffset());

		return false;
	}

}