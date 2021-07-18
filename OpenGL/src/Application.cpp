#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"

using namespace glm;
using namespace test;

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(2);

    if (glewInit() != GLEW_OK)
    {
        cout << "error" << endl;
    }
    cout << glGetString(GL_VERSION) << endl;
    {
    /* Loop until the user closes the window */
    float r = 0.0f;
    float i = 0.05f;
    
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();

    Test* currentTest=nullptr;
    TestMenu* menu = new TestMenu(currentTest);
    currentTest = menu;

    menu->RegisterTest<TestClearColor>("Clear Color");
    menu->RegisterTest<TestTexture2D>("2D Texture");

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        
        ImGui_ImplGlfwGL3_NewFrame();

        if (r > 1.0f) i = -0.05;
        else if (r < 0.0f)
            i = 0.05f;
        r += i;

        if (currentTest)
        {
            currentTest->OnUpdate(0.0f);
            currentTest->OnRender();
            Begin("Test");
           
            if (currentTest != menu && Button("Back"))
            {
                delete currentTest;
                currentTest = menu;
            }
            currentTest->OnImGuiRender();
            End();
        }
        //glDrawArrays(GL_TRIANGLES, 0, 3);

        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    
    if (currentTest != menu)
    {
        delete menu;
    }
    delete currentTest;
   
    }
    
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}