#ifndef LAYER_H
#define LAYER_H

#include "hzpch.h"

#include "Core/Events/Event.h"

namespace Editor {

	class Layer
	{
	public:
		Layer(std::string layerName = "None")
			: l_Name(layerName)
		{
		}

		virtual void OnAttach() = 0;

		virtual void ShutDown() = 0;

		virtual void OnUpdate() = 0;
		virtual void OnEvent(Event& event) = 0;

		inline bool GetStateAtt() const { return l_Attach; }
		inline std::string GetName() const { return l_Name; }

		inline void IsAttached() { l_Attach = true; }

	private:
		std::string l_Name;
		bool l_Attach = false;
	};

}

#endif