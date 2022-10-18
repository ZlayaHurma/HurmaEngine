#include "OpenGLRenderer.h"
#include "IVertexArray.h"
#include "IIndexBuffer.h"

#include <glad/glad.h>
#include "glm/vec4.hpp"

namespace Hurma
{
namespace Render
{

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
        glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
    }

}
}