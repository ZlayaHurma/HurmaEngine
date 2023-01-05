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
        virtual void init(const std::string& vertexsSrc, const std::string& fragmentSrc) = 0;

        virtual bool uploadUniformMat4(const glm::mat4& matrix, const std::string& name) = 0;
        virtual bool uploadUniformVec4(const glm::vec4& vec, const std::string& name) = 0;
        virtual bool uploadUniformVec3(const glm::vec3& vec, const std::string& name) = 0;
        virtual bool uploadUniformInt(int uniformInt, const std::string& name) = 0;
    };

}

}