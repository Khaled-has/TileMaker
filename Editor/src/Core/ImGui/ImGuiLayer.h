#ifndef IMGUILAYER_H
#define IMGUILAYER_H

#include "Core/Layer.h"

#include "Core/Events/MouseEvent.h"
#include "Core/Events/KeyEvent.h"

#include "ImTexture.h"

namespace Editor {
	
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	};

}

#endif