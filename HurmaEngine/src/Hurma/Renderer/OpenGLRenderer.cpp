#include "OpenGLRenderer.h"

#include <glad/glad.h>

#include "IIndexBuffer.h"
#include "IVertexArray.h"
#include "glm/vec4.hpp"
#include "OpenGLVertexBuffer.h"
#include "OpenGLShader.h"
#include "OpenGLIndexBuffer.h"
#include "OpenGLTexture.h"
#include "OpenGLVertexArray.h"

namespace Hurma {
namespace Render {

    void OpenGLRenderer::init()
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    };

    void OpenGLRenderer::setClearColor(const glm::vec4& color) 
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRenderer::clear() 
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderer::drawIndexed(std::shared_ptr<IVertexArray> vertexArray) 
    {
        vertexArray->bind();
        glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(),
            GL_UNSIGNED_INT, nullptr);
        vertexArray->unbind();
    }

    void OpenGLRenderer::setViewport(uint32_t width, uint32_t height) 
    {
        glViewport(0, 0, width, height);
    }

    std::shared_ptr<IVertexArray> OpenGLRenderer::createVertexArray()
    {
        return std::make_shared<OpenGLVertexArray>();
    }

    std::shared_ptr<IVertexBuffer> OpenGLRenderer::createVertexBuffer(VertexComp* vertices, uint32_t size)
    {
        return std::make_shared<OpenGLVertexBuffer>(vertices, size);
    }

    std::shared_ptr<IShader> OpenGLRenderer::createShader(const std::string& vertexsSrc, const std::string& fragmentSrc)
    {
        return std::make_shared<OpenGLShader>(vertexsSrc, fragmentSrc);
    }

    std::shared_ptr<IIndexBuffer> OpenGLRenderer::createIndexBuffer(Index* indices, uint32_t size)
    {
        return std::make_shared<OpenGLIndexBuffer>(indices, size);
    }

    std::shared_ptr<ITexture> OpenGLRenderer::createTexture(uint32_t width, uint32_t height)
    {
        return std::make_shared<OpenGLTexture2D>(width, height);
    }

    std::shared_ptr<Hurma::ITexture> OpenGLRenderer::createTexture(const std::string& path)
    {
        return std::make_shared<OpenGLTexture2D>(path);
    }

}  // namespace Render
}  // namespace Hurma