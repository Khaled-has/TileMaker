#ifndef IMGUILAYER_H
#define IMGUILAYER_H

#include "Core/Layer.h"

#include "Core/Events/MouseEvent.h"
#include "Core/Events/KeyEvent.h"

namespace Editor {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;

		void ShutDown() override {}

	private:

		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMousePressedEvent(MousePressedEvent& e);
		bool OnMouseReleasedEvent(MouseReleasedEvent& e);
		bool OnMouseScrollEvent(MouseScrollEvent& e);
	};

}

#endif