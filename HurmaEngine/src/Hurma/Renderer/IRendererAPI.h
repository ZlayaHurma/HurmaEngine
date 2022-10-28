#pragma once
#include <memory>
#include "glm/vec4.hpp"
#include "Hurma/Core.h"
#include "IVertexBuffer.h"
#include "IIndexBuffer.h"
#include <string>

namespace Hurma
{
    class ITexture;

namespace Render
{
    class IVertexArray;
    class IShader;

    class HURMA_API IRendererAPI
    {
    public:
        virtual void init() = 0;
        virtual void setClearColor(const glm::vec4& color) = 0;
        virtual void setViewport(uint32_t width, uint32_t height) = 0;
        virtual void clear() = 0;
        virtual void drawIndexed(std::shared_ptr<IVertexArray> vertexArray) = 0;

        virtual std::shared_ptr<IVertexArray> createVertexArray() = 0;
        virtual std::shared_ptr<IVertexBuffer> createVertexBuffer(VertexComp* vertices, uint32_t size) = 0;
        virtual std::shared_ptr<IShader> createShader(const std::string& vertexsSrc, const std::string& fragmentSrc) = 0;
        virtual std::shared_ptr<IIndexBuffer> createIndexBuffer(Index* indices, uint32_t size) = 0;
                
        virtual std::shared_ptr<ITexture> createTexture(uint32_t width, uint32_t height) = 0;
        virtual std::shared_ptr<ITexture> createTexture(const std::string& path) = 0;
    };

}
}