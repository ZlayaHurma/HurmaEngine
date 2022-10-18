#include "RenderCommand.h"
#include "OpenGLRenderer.h"

namespace Hurma
{
namespace Render
{
    IRendererAPI* RenderCommand::mRendererAPI = new OpenGLRenderer();

    void RenderCommand::clear() 
    {
        mRendererAPI->clear();
    }

    void RenderCommand::setClearColor(const glm::vec4& color) 
    {
        mRendererAPI->setClearColor(color);
    }

    void RenderCommand::drawIndexed(std::shared_ptr<IVertexArray> vertexArray) 
    {
        mRendererAPI->drawIndexed(vertexArray);
    }

}
}