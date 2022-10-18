#pragma once
#include <stdint.h>
#include "IBindable.h"

namespace Hurma
{
namespace Render
{
    class BufferLayout;

    typedef float VertexComp;

    class HURMA_API IVertexBuffer : public IBindable
    {
    public:
        virtual bool init(VertexComp* vertices, uint32_t size) = 0;

        virtual const BufferLayout& getLayout() const = 0;
        virtual void setLayout(const BufferLayout& layout) = 0;
    };
}
}