#pragma once

#include <GL/glew.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "imGui/imgui.h"
#include "imGui/imgui_impl_glfw_gl3.h"

using namespace ImGui;

using namespace std;

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLclearerror();\
x;\
ASSERT(GLlogcall(#x, __FILE__, __LINE__))

void GLclearerror();

bool GLlogcall(const char* function, const char* file, int line);

class Renderer
{
private:

public:
	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};
