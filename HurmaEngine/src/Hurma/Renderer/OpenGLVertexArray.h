#pragma once
#include "IVertexArray.h"

namespace Hurma {

namespace Render {

    class IIndexBuffer;
    class IVertexBuffer;

    class HURMA_API OpenGLVertexArray : public IVertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void bind() const override;
		void unbind() const override;

		void addVertexBuffer(const std::shared_ptr<IVertexBuffer>& vertexBuffer) override;
		void setIndexBuffer(const std::shared_ptr<IIndexBuffer>& indexBuffer) override;

		const std::vector<std::shared_ptr<IVertexBuffer>>& getVertexBuffers() const { return mVertexBuffers; }
		const std::shared_ptr<IIndexBuffer>& getIndexBuffer() const { return mIndexBuffer; }

	private:
		uint32_t mRendererID;
		uint32_t mVertexBufferIndex = 0;

        #pragma warning(push)
        #pragma warning(disable:4251)
		std::vector<std::shared_ptr<IVertexBuffer>> mVertexBuffers;
		std::shared_ptr<IIndexBuffer> mIndexBuffer;
        #pragma warning(pop)
	};

}

}