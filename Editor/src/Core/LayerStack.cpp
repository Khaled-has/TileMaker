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
		s_Layers.push_back(layer);
	}

	void LayerStack::Push(Layer* layer)
	{

	}

	void LayerStack::OnEvent(Event& event)
	{
		for (int i = s_Layers.size() - 1; i >= 0; i--)
		{
			if (s_Layers[i]->GetStateAtt())
			{
				s_Layers[i]->OnEvent(event);
			}
		}
	}

	void LayerStack::OnUpdate()
	{
		// Layers Update
		for (Layer* layer : s_Layers)
		{
			if (!layer->GetStateAtt())
			{
				layer->OnAttach();
				layer->IsAttached();
			}

			layer->OnUpdate();
		}
	}

}
