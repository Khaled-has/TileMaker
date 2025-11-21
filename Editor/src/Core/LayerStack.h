#ifndef LAYERSTACK_H
#define LAYERSTACK_H

#include "Layer.h"

namespace Editor {

	class LayerStack
	{
	public:
		LayerStack() {}
		~LayerStack();

		void Push_Back(Layer* layer);
		void Push(Layer* layer);

		void OnEvent(Event& event);
		void OnUpdate();

	private:
		std::vector<Layer*> s_Layers;
	};

}

#endif