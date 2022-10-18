#include "OpenGLVertexArray.h"
#include <glad/glad.h>

#include "IVertexBuffer.h"
#include "ShaderDataType.h"
#include "BufferLayout.h"
#include "IIndexBuffer.h"

namespace Hurma {

namespace Render {

    static GLenum shaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:    return GL_FLOAT;
			case ShaderDataType::Float2:   return GL_FLOAT;
			case ShaderDataType::Float3:   return GL_FLOAT;
			case ShaderDataType::Float4:   return GL_FLOAT;
			case ShaderDataType::Mat3:     return GL_FLOAT;
			case ShaderDataType::Mat4:     return GL_FLOAT;
			case ShaderDataType::Int:      return GL_INT;
			case ShaderDataType::Int2:     return GL_INT;
			case ShaderDataType::Int3:     return GL_INT;
			case ShaderDataType::Int4:     return GL_INT;
			case ShaderDataType::Bool:     return GL_BOOL;
		}

		_ASSERTE(false);
		return 0;
	}

    OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &mRendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &mRendererID);
	}

	void OpenGLVertexArray::bind() const
	{
		glBindVertexArray(mRendererID);
	}

	void OpenGLVertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<IVertexBuffer>& vertexBuffer)
	{
		_ASSERTE(vertexBuffer->getLayout().getElements().size());

		glBindVertexArray(mRendererID);
		vertexBuffer->bind();

		const auto& layout = vertexBuffer->getLayout();
		for (const auto& element : layout)
		{
			switch (element.type)
			{
				case ShaderDataType::Float:
				case ShaderDataType::Float2:
				case ShaderDataType::Float3:
				case ShaderDataType::Float4:
				{
					glEnableVertexAttribArray(mVertexBufferIndex);
					glVertexAttribPointer(mVertexBufferIndex,
						element.getComponentCount(),
						shaderDataTypeToOpenGLBaseType(element.type),
						element.normalized ? GL_TRUE : GL_FALSE,
						layout.getStride(),
						(const void*)element.offset);
					mVertexBufferIndex++;
					break;
				}
				case ShaderDataType::Int:
				case ShaderDataType::Int2:
				case ShaderDataType::Int3:
				case ShaderDataType::Int4:
				case ShaderDataType::Bool:
				{
					glEnableVertexAttribArray(mVertexBufferIndex);
					glVertexAttribIPointer(mVertexBufferIndex,
						element.getComponentCount(),
						shaderDataTypeToOpenGLBaseType(element.type),
						layout.getStride(),
						(const void*)element.offset);
					mVertexBufferIndex++;
					break;
				}
				case ShaderDataType::Mat3:
				case ShaderDataType::Mat4:
				{
					uint8_t count = element.getComponentCount();
					for (uint8_t i = 0; i < count; i++)
					{
						glEnableVertexAttribArray(mVertexBufferIndex);
						glVertexAttribPointer(mVertexBufferIndex,
							count,
							shaderDataTypeToOpenGLBaseType(element.type),
							element.normalized ? GL_TRUE : GL_FALSE,
							layout.getStride(),
							(const void*)(element.offset + sizeof(float) * count * i));
						glVertexAttribDivisor(mVertexBufferIndex, 1);
						mVertexBufferIndex++;
					}
					break;
				}
				default:
					_ASSERTE(false);
			}
		}

		mVertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IIndexBuffer>& indexBuffer)
	{
		glBindVertexArray(mRendererID);
		indexBuffer->bind();

		mIndexBuffer = indexBuffer;
	}

}

}