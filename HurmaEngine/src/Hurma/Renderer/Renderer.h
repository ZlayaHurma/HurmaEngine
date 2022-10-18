#pragma once
#include <memory>
#include "Hurma/Core.h"

namespace Hurma 
{
    struct Camera;

namespace Render 
{
    class IVertexArray;
    class IShader;

    class HURMA_API Renderer
    {
    public:
        static void beginScene(std::shared_ptr<Camera> camera);
        static void endScene();
        static void submit(std::shared_ptr<IShader> shader, std::shared_ptr<IVertexArray> vertexArray);

    private:
        #pragma warning(push)
        #pragma warning(disable:4251)
        static std::shared_ptr<Camera> mCamera;
        #pragma warning(pop)
    };

}
}