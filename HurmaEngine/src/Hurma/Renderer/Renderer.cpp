#include "Renderer.h"
#include "RenderCommand.h"
#include "IVertexArray.h"
#include "Hurma/Camera/Camera.h"
#include "Hurma/Renderer/IShader.h"
#include "../Log/Log.h"

namespace Hurma 
{
namespace Render 
{
    std::shared_ptr<Camera> Renderer::mCamera = nullptr;

    void Renderer::beginScene(std::shared_ptr<Camera> camera) 
    {
        mCamera = camera;
    }

    void Renderer::endScene() 
    {
        mCamera = nullptr;    
    }

    void Renderer::submit(std::shared_ptr<IShader> shader, std::shared_ptr<IVertexArray> vertexArray) 
    {
        shader->bind();
        if(!shader->uploadUniformMat4(mCamera->getViewMatrix(), "uViewMatrix"))
            Log::logWarn("uViewMatrix uniform was no passed into the vertex shader. Camera disabled");

        if(!shader->uploadUniformMat4(mCamera->getProjMatrix(), "uProjMatrix"))
            Log::logWarn("uProjMatrix uniform was no passed into the vertex shader. Camera disabled");

        vertexArray->bind();
        RenderCommand::drawIndexed(vertexArray);
    }

}
}
