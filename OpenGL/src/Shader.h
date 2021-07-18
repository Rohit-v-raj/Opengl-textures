#pragma once
#include <GL/glew.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include <string>
#include <unordered_map>

#include"glm/glm.hpp"

using namespace std;

struct ShaderProgramSource
{
	string Vertexsource;
	string Fragmentsource;
};

class Shader
{
private:
	unsigned int m_RendererID;
	string filepath;
	unordered_map<string, int> m_UniformLocationCache;

public:
	Shader(const string& file);

	~Shader();

	void Bind() const;

	void UnBind() const;

	void SetUniform1i(const string& name, int value);

	void SetUniform4f(const string& name, float v1, float v2, float v3, float v4);

	void SetUniformMat4f(const string& name, const glm::mat4& matrix);
private:

	ShaderProgramSource ParseShader(const string& filepath);

	int GetUniformLocation(const string& name);

	unsigned int CompileShader(unsigned int type, const string& source);

	unsigned int CreateShader(const string& vertexShader, const string& fragmentShader);

};
