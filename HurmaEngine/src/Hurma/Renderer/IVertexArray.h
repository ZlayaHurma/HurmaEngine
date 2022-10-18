#pragma once

#include "Hurma/Renderer/IBindable.h"
#include <memory>
#include <vector>

namespace Hurma {

namespace Render {

    class IVertexBuffer;
    class IIndexBuffer;

	class HURMA_API IVertexArray : public IBindable
	{
	public:
		virtual ~IVertexArray() = default;

		virtual void addVertexBuffer(const std::shared_ptr<IVertexBuffer>& vertexBuffer) = 0;
		virtual void setIndexBuffer(const std::shared_ptr<IIndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<std::shared_ptr<IVertexBuffer>>& getVertexBuffers() const = 0;
		virtual const std::shared_ptr<IIndexBuffer>& getIndexBuffer() const = 0;
	};

}
}