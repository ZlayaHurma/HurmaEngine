#pragma once
#include <string>

namespace Hurma {

    class Event;

	class Layer
	{
	 public:
		Layer(const std::string& name = "Layer") { mDebugName = name; }
		virtual ~Layer() = default;

		virtual void onAttach() = 0;
		virtual void onDetach() = 0;
		virtual void onUpdate() = 0;
		virtual void onEvent(const Event& event) = 0;

		const std::string& getName() const { return mDebugName; }

	 protected:
		std::string mDebugName;
	};

}