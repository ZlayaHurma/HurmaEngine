#pragma once
#include "IIndexBuffer.h"

namespace Hurma
{
namespace Render
{

    class HURMA_API OpenGLIndexBuffer : public IIndexBuffer 
    {
    public:
        OpenGLIndexBuffer(Index* indices, uint32_t size);
        ~OpenGLIndexBuffer();
    
        void bind() const override;
    
        void unbind() const override;
        
        bool init(Index* indices, uint32_t size) override;

        uint32_t getCount() const override { return mCount; }
    
    private:
        uint32_t mRendererID;
        uint32_t mCount;
    };

}
}