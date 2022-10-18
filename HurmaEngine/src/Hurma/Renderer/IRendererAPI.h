#pragma once
#include <memory>
#include "glm/vec4.hpp"
#include "Hurma/Core.h"

namespace Hurma
{
namespace Render
{
    class IVertexArray;

    class HURMA_API IRendererAPI
    {
    public:
        virtual void setClearColor(const glm::vec4& color) = 0;
        virtual void clear() = 0;
        virtual void drawIndexed(std::shared_ptr<IVertexArray> vertexArray) = 0;
    };

}
}