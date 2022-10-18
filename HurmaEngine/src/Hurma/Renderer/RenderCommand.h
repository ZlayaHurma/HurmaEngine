#pragma once
#include <memory>
#include "glm/vec4.hpp"
#include "Hurma/Core.h"

namespace Hurma
{
namespace Render
{
    class IRendererAPI;
    class IVertexArray;

    class HURMA_API RenderCommand
    {
    public:
        static void clear();
        static void setClearColor(const glm::vec4& color);
        static void drawIndexed(std::shared_ptr<IVertexArray> vertexArray);

    private:
        static IRendererAPI* mRendererAPI;
    };

}
}