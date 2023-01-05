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
    //// Lighting
    ///////////////////////////////////////////////////////////////

    glm::vec3 Renderer::mLightDir = {0.f, -1.f, 0.f};

    ///////////////////////////////////////////////////////////////
    //// Drawing buffers
    ///////////////////////////////////////////////////////////////

    // Quad
    static std::shared_ptr<IVertexArray> QUAD_VERTEX_ARRAY {};
    static std::shared_ptr<IShader> QUAD_TEXTURE_SHADER {};
    static std::shared_ptr<IShader> QUAD_COLOR_SHADER {};

    // Cube
    static std::shared_ptr<IVertexArray> CUBE_VERTEX_ARRAY {};
    static std::shared_ptr<IShader> CUBE_COLOR_SHADER {};

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

        std::string colorFragShader = R"(
            #version 330 core

            layout(location = 0) out vec4 color;


            uniform vec4 uColor;

            void main(){
              color = uColor;
            }
        )";

        QUAD_TEXTURE_SHADER = Renderer::createShader(vert, textureFragShader);
        QUAD_COLOR_SHADER   = Renderer::createShader(vert,   colorFragShader);
    }

    void setupCubeRenderData()
    {
        CUBE_VERTEX_ARRAY = Renderer::createVertexArray();

        VertexComp cubeVerticesData[24 * 6] 
        {
            /*pos*/  0.5f, -0.5f, -0.5f, /*normal*/  0.f, -1.f,  0.f, // 0    0
            /*pos*/  0.5f, -0.5f, -0.5f, /*normal*/  1.f,  0.f,  0.f, // 1
            /*pos*/  0.5f, -0.5f, -0.5f, /*normal*/  0.f,  0.f, -1.f, // 2
                                                                      
            /*pos*/  0.5f,  0.5f, -0.5f, /*normal*/  0.f,  1.f,  0.f, // 3    1
            /*pos*/  0.5f,  0.5f, -0.5f, /*normal*/  1.f,  0.f,  0.f, // 4
            /*pos*/  0.5f,  0.5f, -0.5f, /*normal*/  0.f,  0.f, -1.f, // 5
                                                                       
            /*pos*/ -0.5f,  0.5f, -0.5f, /*normal*/  0.f,  1.f,  0.f, // 6    2
            /*pos*/ -0.5f,  0.5f, -0.5f, /*normal*/ -1.f,  0.f,  0.f, // 7
            /*pos*/ -0.5f,  0.5f, -0.5f, /*normal*/  0.f,  0.f, -1.f, // 8
                                                                      
            /*pos*/ -0.5f, -0.5f, -0.5f, /*normal*/  0.f, -1.f,  0.f, // 9    3
            /*pos*/ -0.5f, -0.5f, -0.5f, /*normal*/ -1.f,  0.f,  0.f, // 10
            /*pos*/ -0.5f, -0.5f, -0.5f, /*normal*/  0.f,  0.f, -1.f, // 11
                                                                      
            /*pos*/  0.5f, -0.5f,  0.5f, /*normal*/  0.f, -1.f,  0.f, // 12   4
            /*pos*/  0.5f, -0.5f,  0.5f, /*normal*/  1.f,  0.f,  0.f, // 13
            /*pos*/  0.5f, -0.5f,  0.5f, /*normal*/  0.f,  0.f,  1.f, // 14
                                                                      
            /*pos*/  0.5f,  0.5f,  0.5f, /*normal*/  0.f,  1.f,  0.f, // 15   5
            /*pos*/  0.5f,  0.5f,  0.5f, /*normal*/  1.f,  0.f,  0.f, // 16
            /*pos*/  0.5f,  0.5f,  0.5f, /*normal*/  0.f,  0.f,  1.f, // 17
                                                                      
            /*pos*/ -0.5f,  0.5f,  0.5f, /*normal*/  0.f,  1.f,  0.f, // 18   6
            /*pos*/ -0.5f,  0.5f,  0.5f, /*normal*/ -1.f,  0.f,  0.f, // 19
            /*pos*/ -0.5f,  0.5f,  0.5f, /*normal*/  0.f,  0.f,  1.f, // 20
                                                                      
            /*pos*/ -0.5f, -0.5f,  0.5f, /*normal*/  0.f, -1.f,  0.f, // 21   7
            /*pos*/ -0.5f, -0.5f,  0.5f, /*normal*/ -1.f,  0.f,  0.f, // 22
            /*pos*/ -0.5f, -0.5f,  0.5f, /*normal*/  0.f,  0.f,  1.f, // 23
        };
        std::shared_ptr<IVertexBuffer> cubeVertexBuffer = Renderer::createVertexBuffer(cubeVerticesData, sizeof(cubeVerticesData));
        cubeVertexBuffer->setLayout({
            {ShaderDataType::Float3, "position"},
            {ShaderDataType::Float3, "normal"}
        });

        constexpr uint32_t trianglesNum = 2 * 6;
        Index indices[trianglesNum * 3] 
        {
            1, 4, 13,
            4, 16, 13,
            14, 17, 23,
            17, 20, 23,
            3, 6, 15,
            6, 18, 15,
            9, 0, 12,
            9, 12, 21,
            11, 5, 2,
            11, 8, 5,
            10, 22, 19,
            19, 7, 10
        };
        std::shared_ptr<IIndexBuffer> cubeIndexBuffer = Renderer::createIndexBuffer(indices, sizeof(indices));
        CUBE_VERTEX_ARRAY->addVertexBuffer(cubeVertexBuffer);
        CUBE_VERTEX_ARRAY->setIndexBuffer(cubeIndexBuffer);

        std::string vert = R"(
            #version 330 core

            layout(location = 0) in vec3 aPosition;
            layout(location = 1) in vec3 aNormal;

            uniform mat4 uProjMatrix;
            uniform mat4 uViewMatrix;
            uniform mat4 uTransformMatrix;

            out vec3 vNormal;

            void main() {
                gl_Position = uProjMatrix * uViewMatrix * uTransformMatrix * vec4(aPosition, 1.0);
                vNormal = aNormal;
            }
        )";

        std::string colorFragShader = R"(
            #version 330 core
            layout(location = 0) out vec4 color;

            in vec3 vNormal;

            uniform vec4 uColor;
            uniform vec3 uLightDir;

            void main() {
              float lightFactor = -1.f * dot(vNormal, uLightDir);
              if(lightFactor < 0.1)
                lightFactor = 0.1;
                
              vec3 color3 = vec3(uColor.x, uColor.y, uColor.z);
              color = vec4(color3 * lightFactor, uColor.w);
            }
        )";

        CUBE_COLOR_SHADER = Renderer::createShader(vert, colorFragShader);
    }

    void Renderer::init() 
    {
        mRendererAPI->init();
        setupQuadRenderData();
        setupCubeRenderData();
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
        // mCamera = nullptr;    
    }

    void Renderer::submit(std::shared_ptr<IShader> shader, std::shared_ptr<IVertexArray> vertexArray) 
    {
        shader->bind();
        if(!shader->uploadUniformMat4(mCamera->getViewMatrix(), "uViewMatrix"))
            Log::logWarn("uViewMatrix uniform was no passed into the vertex shader. Camera disabled");

        if(!shader->uploadUniformMat4(mCamera->getProjMatrix(), "uProjMatrix"))
            Log::logWarn("uProjMatrix uniform was no passed into the vertex shader. Camera disabled");

        drawIndexed(vertexArray);
    }

    void Renderer::clear() 
    {
        mRendererAPI->clear();
    }

    void Renderer::setViewport(uint32_t width, uint32_t height) 
    {
        mRendererAPI->setViewport(width, height);
        mCamera->setAspectRatio(static_cast<float>(width) / static_cast<float>(height));
    }

    void Renderer::setClearColor(const glm::vec4& color) 
    {
        mRendererAPI->setClearColor(color);
    }

    void Renderer::drawIndexed(std::shared_ptr<IVertexArray> vertexArray) 
    {
        mRendererAPI->drawIndexed(vertexArray);
    }

    void Renderer::drawCube(const glm::vec3& worldPosition, float sideLength, const glm::vec4& color)
    {
        auto translatedMatrix = glm::translate(glm::mat4(1.f), worldPosition );
        auto scaledMatrix = glm::scale(translatedMatrix, glm::vec3(sideLength));

        auto transformMatrix = scaledMatrix;

        CUBE_COLOR_SHADER->bind();
        CUBE_COLOR_SHADER->uploadUniformMat4(transformMatrix, "uTransformMatrix");
        CUBE_COLOR_SHADER->uploadUniformVec4(color, "uColor");
        CUBE_COLOR_SHADER->uploadUniformVec3(mLightDir, "uLightDir");

        submit(CUBE_COLOR_SHADER, CUBE_VERTEX_ARRAY);
    }

    void Renderer::draw2DQuad(const glm::vec2& worldPosition, float sideLength, float angleRad, const glm::vec4& color)
    {
        auto translatedMatrix = glm::translate(glm::mat4(1.f), { worldPosition, 0.0f } );
        auto rotatedMatrix = glm::rotate(translatedMatrix, angleRad, glm::vec3(0.f, 0.f, 1.f));
        auto scaledMatrix = glm::scale(rotatedMatrix, glm::vec3(sideLength, sideLength, 1.f));

        auto transformMatrix = scaledMatrix;

        QUAD_COLOR_SHADER->bind();
        QUAD_COLOR_SHADER->uploadUniformMat4(transformMatrix, "uTransformMatrix");
        QUAD_COLOR_SHADER->uploadUniformVec4(color, "uColor");

        submit(QUAD_COLOR_SHADER, QUAD_VERTEX_ARRAY);
    }

    void Renderer::draw2DQuad(const glm::vec2& worldPosition, float sideLength, float angleRad, std::shared_ptr<ITexture> texture)
    {
        auto translatedMatrix = glm::translate(glm::mat4(1.f), { worldPosition, 0.0f } );
        auto rotatedMatrix = glm::rotate(translatedMatrix, angleRad, glm::vec3(0.f, 0.f, 1.f));
        auto scaledMatrix = glm::scale(rotatedMatrix, glm::vec3(sideLength, sideLength, 1.f));

        auto transformMatrix = scaledMatrix;
        
        QUAD_TEXTURE_SHADER->bind();
        QUAD_TEXTURE_SHADER->uploadUniformMat4(transformMatrix, "uTransformMatrix");

        const static int textureSlot = 0;
        texture->bind(textureSlot);
        QUAD_TEXTURE_SHADER->uploadUniformInt(textureSlot, "uTexture");

        submit(QUAD_TEXTURE_SHADER, QUAD_VERTEX_ARRAY);
    }

    void Renderer::setLightDirection(const glm::vec3& lightDir)
    {
        mLightDir = lightDir;
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
