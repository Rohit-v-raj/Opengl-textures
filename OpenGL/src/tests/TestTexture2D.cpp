#include "TestTexture2D.h"
#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

//Math Libraries
#include "glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"


test::TestTexture2D::TestTexture2D()
    :m_TranslationA(200, 200, 0), m_TranslationB(400, 200, 0) 
{
    float positions[] = {
        -50.0f, -50.0f, 0.0f, 0.0f,  //0
         50.0f, -50.0f, 1.0f, 0.0f,  //1
         50.0f,  50.0f, 1.0f, 1.0f,  //2
        -50.0f,  50.0f, 0.0f, 1.0f  //3
    };

    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    
    vb=make_unique<VertexBuffer>(positions,4*4*sizeof(float));
    layout = make_unique<VertexBufferLayout>();
    layout->Push<float>(2);
    layout->Push<float>(2);
    va = make_unique<VertexArray>();
    va->AddBuffer(*vb, *layout);

    proj = ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    view = translate(mat4(1.0f), vec3(0, 0, 0));

    ib=make_unique<IndexBuffer>(indices, 6);


    shader= make_unique<Shader>("res/shaders/basic.shader");
    shader->Bind();
 /*   shader->SetUniform4f("u_color", 0.2f, 0.3f, 0.8f, 1.0f);*/

    texture=make_unique<Texture>("res/textures/LogoMakr-7gtZW5 - Copy.png");
    texture->Bind(0);
    shader->SetUniform1i("u_Texture", 0);


}

test::TestTexture2D::~TestTexture2D()
{
}

void test::TestTexture2D::OnUpdate(float deltaTime)
{
}

void test::TestTexture2D::OnRender()
{
    GLCall(glClearColor(0.0f,0.0f,0.0f,1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));

    Renderer renderer;

    {
        mat4 model = translate(mat4(1.0f), m_TranslationA);
        mat4 mvp = proj * view * model;

        shader->Bind();
        shader->SetUniformMat4f("u_MVP", mvp);
        //shader.SetUniform4f("u_color", r, 1.0f, r, 1.0f);
        renderer.Draw(*va, *ib, *shader);
    }

    {
        mat4 model = translate(mat4(1.0f), m_TranslationB);
        mat4 mvp = proj * view * model;

        shader->Bind();
        shader->SetUniformMat4f("u_MVP", mvp);
        renderer.Draw(*va, *ib, *shader);
    }
}

void test::TestTexture2D::OnImGuiRender()
{
    ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
    ImGui::SliderFloat3("TranslationA", &m_TranslationA.x, 0.0f, 960.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::SliderFloat3("TranslationB", &m_TranslationB.x, 0.0f, 960.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
