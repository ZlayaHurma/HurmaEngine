#include "OpenGLVertexBuffer.h"
#include <glad/glad.h>

namespace Hurma
{
namespace Render
{

    OpenGLVertexBuffer::OpenGLVertexBuffer(VertexComp* vertices, uint32_t size) 
    {
        init(vertices, size);
    }
    
    OpenGLVertexBuffer::~OpenGLVertexBuffer() 
    {
        glDeleteBuffers(1, &mRendererID);
    }

    void OpenGLVertexBuffer::bind() const 
    {
        glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
    }
    
    void OpenGLVertexBuffer::unbind() const 
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    bool OpenGLVertexBuffer::init(VertexComp* vertices, uint32_t size)
    {
        glCreateBuffers(1, &mRendererID);
		glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

        return true;
    }

}
}