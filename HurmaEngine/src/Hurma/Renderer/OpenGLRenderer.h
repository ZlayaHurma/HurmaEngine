#pragma once
#include "IRendererAPI.h"
#include <memory>
#include "glm/vec4.hpp"

namespace Hurma
{
namespace Render
{
    class OpenGLRenderer : public IRendererAPI
    {
    public:
        void setClearColor(const glm::vec4& color) override;
        void clear() override;
        void drawIndexed(std::shared_ptr<IVertexArray> vertexArray) override;
    };

}
}