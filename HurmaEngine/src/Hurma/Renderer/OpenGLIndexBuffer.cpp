#include "OpenGLIndexBuffer.h"
#include <glad/glad.h>

namespace Hurma
{
namespace Render
{

    OpenGLIndexBuffer::OpenGLIndexBuffer(Index* indices, uint32_t size) 
        : mCount(size / sizeof(uint32_t))
    {
        init(indices, size);
    }
    
    OpenGLIndexBuffer::~OpenGLIndexBuffer() 
    {
        glDeleteBuffers(1, &mRendererID);
    }

    void OpenGLIndexBuffer::bind() const 
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
    }
    
    void OpenGLIndexBuffer::unbind() const 
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    bool OpenGLIndexBuffer::init(Index* indices, uint32_t size)
    {
        glCreateBuffers(1, &mRendererID);
		
		// GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
		// Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state. 
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        return true;
    }

}
}