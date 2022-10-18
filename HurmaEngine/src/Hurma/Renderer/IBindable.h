#pragma once
#include "Hurma/Core.h"

namespace Hurma
{
namespace Render
{
    class HURMA_API IBindable 
    {
    public:
        virtual void bind() const = 0;
        virtual void unbind() const  = 0;

        virtual ~IBindable() = default;
    };
}
}