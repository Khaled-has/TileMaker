#ifndef LAYER_H
#define LAYER_H

#include "pch.h"

#include "Core/Events/Event.h"

namespace Editor {

	class Layer
	{
	public:
		Layer(std::string layerName = "None")
			: l_Name(layerName)
		{
		}

		virtual void OnAttach() {};
		virtual void OnDetach() {};

		virtual void OnUpdate() {};
		virtual void OnImGuiRender() {};
		virtual void OnEvent(Event& event) {};

		inline std::string GetName() const { return l_Name; }

	private:
		std::string l_Name;
	};

}

#endif