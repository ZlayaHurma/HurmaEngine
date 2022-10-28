#include "Renderer.h"
#include "IVertexArray.h"
#include "Hurma/Camera/Camera.h"
#include "Hurma/Renderer/IShader.h"
#include "Hurma/Log/Log.h"
#include "OpenGLRenderer.h"
#include "ShaderDataType.h"
#include "BufferLayout.h"
#include "ITexture.h"

namespace Hurma 
{
namespace Render 
{
    std::shared_ptr<Camera> Renderer::mCamera = nullptr;
    IRendererAPI* Renderer::mRendererAPI = new OpenGLRenderer();

    ///////////////////////////////////////////////////////////////
    //// Drawing buffers
    ///////////////////////////////////////////////////////////////

    static std::shared_ptr<IVertexArray> QUAD_VERTEX_ARRAY {};
    static std::shared_ptr<IShader> QUAD_SHADER {};

    ///////////////////////////////////////////////////////////////

    
    void setupQuadRenderData()
    {
        QUAD_VERTEX_ARRAY = Renderer::createVertexArray();

        VertexComp verticesData[4 * 5] 
        {
            /*pos*/ -0.5f, -0.5f, 0.0f, /*tex*/ 0.f, 0.f,
            /*pos*/  0.5f, -0.5f, 0.0f, /*tex*/ 1.f, 0.f,
            /*pos*/  0.5f,  0.5f, 0.0f, /*tex*/ 1.f, 1.f,
            /*pos*/ -0.5f,  0.5f, 0.0f, /*tex*/ 0.f, 1.f,
        };
        std::shared_ptr<IVertexBuffer> quadVertexBuffer = Renderer::createVertexBuffer(verticesData, sizeof(verticesData));
        quadVertexBuffer->setLayout({
            {ShaderDataType::Float3, "position"},
            {ShaderDataType::Float2, "textureCoord"}
        });

        Index indices[6] 
        {
            0, 1, 2, 0, 2, 3            
        };
        std::shared_ptr<IIndexBuffer> quadIndexBuffer = Renderer::createIndexBuffer(indices, sizeof(indices));
        QUAD_VERTEX_ARRAY->addVertexBuffer(quadVertexBuffer);
        QUAD_VERTEX_ARRAY->setIndexBuffer(quadIndexBuffer);
        QUAD_VERTEX_ARRAY->unbind();

        std::string vert = R"(
            #version 330 core

            layout(location = 0) in vec3 aPosition;
            layout(location = 1) in vec2 aTextureCoords;

            uniform mat4 uProjMatrix;
            uniform mat4 uViewMatrix;
            uniform mat4 uTransformMatrix;

            out vec2 vTextureCoords;

            void main(){
                gl_Position = uProjMatrix * uViewMatrix * uTransformMatrix * vec4(aPosition, 1.0);
                vTextureCoords = aTextureCoords;
            }
        )";

        std::string textureFragShader = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec2 vTextureCoords;

            uniform sampler2D uTexture;

            void main(){
              color = texture(uTexture, vTextureCoords);
            }
        )";

        QUAD_SHADER = Renderer::createShader(vert, textureFragShader);
    }

    void Renderer::init() 
    {
        mRendererAPI->init();
        setupQuadRenderData();
    }

    void Renderer::onWindowResize(uint32_t width, uint32_t height) 
    {
        setViewport(width, height);    
    }

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
        drawIndexed(vertexArray);
    }

    void Renderer::clear() 
    {
        mRendererAPI->clear();
    }

    void Renderer::setViewport(uint32_t width, uint32_t height) 
    {
        mRendererAPI->setViewport(width, height);
    }

    void Renderer::setClearColor(const glm::vec4& color) 
    {
        mRendererAPI->setClearColor(color);
    }

    void Renderer::drawIndexed(std::shared_ptr<IVertexArray> vertexArray) 
    {
        mRendererAPI->drawIndexed(vertexArray);
    }

    void Renderer::draw2DQuad(const glm::vec2& worldPosition, float sideLength, float angleRad, const glm::vec4& color)
    {

    }

    void Renderer::draw2DQuad(const glm::vec2& worldPosition, float sideLength, float angleRad, std::shared_ptr<ITexture> texture)
    {
        auto translatedMatrix = glm::translate(glm::mat4(1.f), { worldPosition, 0.0f } );
        auto rotatedMatrix = glm::rotate(translatedMatrix, angleRad, glm::vec3(0.f, 0.f, 1.f));
        auto scaledMatrix = glm::scale(rotatedMatrix, glm::vec3(sideLength, sideLength, 1.f));

        auto transformMatrix = scaledMatrix;

        QUAD_SHADER->uploadUniformMat4(transformMatrix, "uTransformMatrix");
        QUAD_SHADER->uploadUniformMat4(mCamera->getViewMatrix(), "uViewMatrix");
        QUAD_SHADER->uploadUniformMat4(mCamera->getProjMatrix(), "uProjMatrix");

        const static int textureSlot = 0;
        texture->bind(textureSlot);
        QUAD_SHADER->uploadUniformInt(textureSlot, "uTexture");

        submit(QUAD_SHADER, QUAD_VERTEX_ARRAY);
    }

    std::shared_ptr<IVertexArray> Renderer::createVertexArray()
    {
        return mRendererAPI->createVertexArray();
    }

    std::shared_ptr<IVertexBuffer> Renderer::createVertexBuffer(VertexComp* vertices, uint32_t size)
    {
        return mRendererAPI->createVertexBuffer(vertices, size);
    }

    std::shared_ptr<IShader> Renderer::createShader(const std::string& vertexsSrc, const std::string& fragmentSrc)
    {
        return mRendererAPI->createShader(vertexsSrc, fragmentSrc);
    }

    std::shared_ptr<IIndexBuffer> Renderer::createIndexBuffer(Index* indices, uint32_t size)
    {
        return mRendererAPI->createIndexBuffer(indices, size);
    }

    std::shared_ptr<ITexture> Renderer::createTexture(uint32_t width, uint32_t height)
    {
        return mRendererAPI->createTexture(width, height);
    }

    std::shared_ptr<Hurma::ITexture> Renderer::createTexture(const std::string& path)
    {
        return mRendererAPI->createTexture(path);
    }
}
}
