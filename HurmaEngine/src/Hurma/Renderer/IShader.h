#pragma once
#include "IBindable.h"
#include "Hurma/Core.h"
#include "glm/matrix.hpp"
#include <string>

namespace Hurma {

namespace Render {

    class HURMA_API IShader : public IBindable
	{
    public:
        virtual bool uploadUniformMat4(const glm::mat4& matrix, const std::string& name) = 0;
    };

}

}