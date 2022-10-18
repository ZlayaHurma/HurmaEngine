#pragma once
#include "IVertexBuffer.h"
#include "BufferLayout.h"

namespace Hurma
{
namespace Render
{

    class HURMA_API OpenGLVertexBuffer : public IVertexBuffer 
    {
    public:
        OpenGLVertexBuffer(VertexComp* vertices, uint32_t size);
        ~OpenGLVertexBuffer();
    
        void bind() const override;
    
        void unbind() const override;
    
        bool init(VertexComp* vertices, uint32_t size) override;

        const BufferLayout& getLayout() const override { return mLayout; }
		void setLayout(const BufferLayout& layout) override { mLayout = layout; }
    
    private:
        uint32_t mRendererID;
        BufferLayout mLayout;
    };

}
}