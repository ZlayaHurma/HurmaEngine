#pragma once
#include <memory>
#include "Hurma/Core.h"
#include "IRendererAPI.h"
#include "glm/ext/matrix_float3x3.hpp"

namespace Hurma 
{
    class Camera;

namespace Render 
{
    class IVertexArray;
    class IShader;

    class HURMA_API Renderer
    {
    public:
        static void init();

        static void beginScene(std::shared_ptr<Camera> camera);
        static void endScene();

        static void onWindowResize(uint32_t width, uint32_t height);
        static void clear();
        static void setClearColor(const glm::vec4& color);

        static void submit(std::shared_ptr<IShader> shader, std::shared_ptr<IVertexArray> vertexArray);

        static void draw2DQuad(const glm::vec2& worldPosition, float sideLength, float angleRad, const glm::vec4& color);
        static void draw2DQuad(const glm::vec2& worldPosition, float sideLength, float angleRad, std::shared_ptr<ITexture> texture);

        static void drawCube(const glm::vec3& worldPosition, float sideLength, const glm::vec4& color);
        
        static void setLightDirection(const glm::vec3& lightDir);

        static std::shared_ptr<IVertexArray> createVertexArray();
        static std::shared_ptr<IVertexBuffer> createVertexBuffer(VertexComp* vertices, uint32_t size);
        static std::shared_ptr<IShader> createShader(const std::string& vertexsSrc, const std::string& fragmentSrc);
        static std::shared_ptr<IIndexBuffer> createIndexBuffer(Index* indices, uint32_t size);
       
        static std::shared_ptr<ITexture> createTexture(uint32_t width, uint32_t height);
        static std::shared_ptr<ITexture> createTexture(const std::string& path);

    private:
        static void drawIndexed(std::shared_ptr<IVertexArray> vertexArray);
        static void setViewport(uint32_t width, uint32_t height);

    private:
        #pragma warning(push)
        #pragma warning(disable:4251)
        static std::shared_ptr<Camera> mCamera;
        static glm::vec3 mLightDir;
        #pragma warning(pop)

        static IRendererAPI* mRendererAPI;
    };

}
}