#include "LayerStack.h"

namespace Editor {

	LayerStack::~LayerStack()
	{
		for (Layer* layer : s_Layers)
		{
			delete layer;
		}
	}

	void LayerStack::Push_Back(Layer* layer)
	{
		layer->OnAttach();
		s_Layers.push_back(layer);
	}

	void LayerStack::Push(Layer* layer)
	{

	}

	void LayerStack::OnEvent(Event& event)
	{
		for (int i = s_Layers.size() - 1; i >= 0; i--)
		{
			s_Layers[i]->OnEvent(event);
		}
	}

	void LayerStack::OnUpdate()
	{
		// Layers Update
		for (Layer* layer : s_Layers)
		{
			layer->OnUpdate();
		}
	}

	void LayerStack::OnImGuiRender()
	{
		// ImGui Rendering
		for (Layer* layer : s_Layers)
		{
			layer->OnImGuiRender();
		}
	}

}
