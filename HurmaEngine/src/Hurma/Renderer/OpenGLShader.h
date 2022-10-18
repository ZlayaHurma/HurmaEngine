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
        virtual ~OpenGLShader();

        void bind() const override;
        void unbind() const override;

        bool uploadUniformMat4(const glm::mat4& matrix, const std::string& name) override;

    private:
        uint32_t mProgram;
    };
}

}