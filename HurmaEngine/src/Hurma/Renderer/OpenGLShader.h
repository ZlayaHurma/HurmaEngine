#pragma once
#include <string>
#include "IShader.h"

namespace Hurma
{
namespace Render
{
    class HURMA_API OpenGLShader : public IShader
    {
    public:
        OpenGLShader(const std::string& vertexsSrc, const std::string& fragmentSrc);

        void init(const std::string& vertexsSrc, const std::string& fragmentSrc) override;
        virtual ~OpenGLShader();

        void bind() const override;
        void unbind() const override;

        bool uploadUniformMat4(const glm::mat4& matrix, const std::string& name) override;
        bool uploadUniformVec4(const glm::vec4& vec, const std::string& name) override;
        bool uploadUniformVec3(const glm::vec3& vec, const std::string& name) override;
        bool uploadUniformInt(int uniformInt, const std::string& name) override;

       private:
        uint32_t mProgram;
    };
}

}