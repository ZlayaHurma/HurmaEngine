#pragma once
#include <string>
#include "Core.h"

namespace Hurma {

    class Event;

	class HURMA_API Layer
	{
	 public:
		Layer(const std::string& name = "Layer") { mDebugName = name; }
		virtual ~Layer() = default;

		virtual void onAttach() = 0;
		virtual void onDetach() = 0;
		virtual void onUpdate(double deltaTimeSec) = 0;
		virtual void onEvent(Event& event) = 0;
        virtual void onImGuiRender() = 0;

		const std::string& getName() const { return mDebugName; }

	 protected:
        #pragma warning(push)
        #pragma warning(disable:4251)
		std::string mDebugName;
        #pragma warning(pop)
	};

}