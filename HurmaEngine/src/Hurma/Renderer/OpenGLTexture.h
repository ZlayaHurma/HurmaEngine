#pragma once

#include "Hurma/Renderer/ITexture.h"

#include <glad/glad.h>

namespace Hurma {

	class HURMA_API OpenGLTexture2D : public ITexture
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t getWidth() const override { return mWidth;  }
		virtual uint32_t getHeight() const override { return mHeight; }
		virtual uint32_t getRendererID() const override { return mRendererID; }

		virtual const std::string& getPath() const override { return mPath; }
		
		virtual void setData(void* data, uint32_t size) override;

		virtual void bind(uint32_t slot = 0) const override;

		virtual bool isLoaded() const override { return mIsLoaded; }

		virtual bool operator==(const ITexture& other) const override
		{
			return mRendererID == other.getRendererID();
		}
	private:

        #pragma warning(push)
        #pragma warning(disable:4251)
		std::string mPath;
		#pragma warning(pop)

        bool mIsLoaded = false;
		uint32_t mWidth, mHeight;
		uint32_t mRendererID;
		GLenum mInternalFormat, mDataFormat;
	};

}