#ifndef IMGUILAYER_H
#define IMGUILAYER_H

#include "Core/Layer.h"

#include "Core/Events/MouseEvent.h"

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

		void OnMouseMovedEvent(MouseMovedEvent& e);
		void OnMousePressedEvent(MousePressedEvent& e);
		void OnMouseReleasedEvent(MouseReleasedEvent& e);
		void OnMouseScrollEvent(MouseScrollEvent& e);
	};

}

#endif