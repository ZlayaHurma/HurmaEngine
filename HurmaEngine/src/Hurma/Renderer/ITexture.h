#pragma once
#include <string>
#include "Hurma/Core.h"

namespace Hurma {

	class HURMA_API ITexture
	{
	public:
		virtual ~ITexture() = default;

		virtual uint32_t getWidth() const = 0;
		virtual uint32_t getHeight() const = 0;
		virtual uint32_t getRendererID() const = 0;

		virtual const std::string& getPath() const = 0;

		virtual void setData(void* data, uint32_t size) = 0;

		virtual void bind(uint32_t slot = 0) const = 0;

		virtual bool isLoaded() const = 0;

		virtual bool operator==(const ITexture& other) const = 0;
	};
}