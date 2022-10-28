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
        void init() override;
        void setClearColor(const glm::vec4& color) override;
        void clear() override;
        void drawIndexed(std::shared_ptr<IVertexArray> vertexArray) override;
        void setViewport(uint32_t width, uint32_t height) override;

        std::shared_ptr<IVertexArray> createVertexArray() override;

        std::shared_ptr<IVertexBuffer> createVertexBuffer(VertexComp* vertices, uint32_t size) override;

        std::shared_ptr<IShader> createShader(const std::string& vertexsSrc, const std::string& fragmentSrc) override;

        std::shared_ptr<IIndexBuffer> createIndexBuffer(Index* indices, uint32_t size) override;

        std::shared_ptr<ITexture> createTexture(uint32_t width, uint32_t height) override;

        std::shared_ptr<ITexture> createTexture(const std::string& path) override;
    };

}
}