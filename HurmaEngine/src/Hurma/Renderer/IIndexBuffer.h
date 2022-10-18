#pragma once
#include <stdint.h>
#include "IBindable.h"

namespace Hurma
{
namespace Render
{
    typedef uint32_t Index;
    
    class HURMA_API IIndexBuffer : public IBindable
    {
    public:
        virtual bool init(Index* indices, uint32_t size) = 0;
        virtual uint32_t getCount() const = 0;
    };
}
}