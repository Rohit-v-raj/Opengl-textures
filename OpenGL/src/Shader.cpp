#include "Shader.h"
#include "Renderer.h"

Shader::Shader(const string& file)
    :m_RendererID(0), filepath(file)
{
	GLCall(ShaderProgramSource source = ParseShader(file));

	GLCall(m_RendererID = CreateShader(source.Vertexsource, source.Fragmentsource));
}
Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::UnBind() const
{
    glUseProgram(0);
}


ShaderProgramSource Shader::ParseShader(const string& filepath)
{
    ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    string line;
    stringstream ss[2];

    ShaderType type = ShaderType::NONE;

    while (getline(stream, line)) {
        if (line.find("shader") != string::npos)
        {
            if (line.find("#vertex") != string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << "\n";
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)_alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        cout << "failed" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << endl;
        cout << message << endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}
unsigned int Shader::CreateShader(const string& vertexShader, const string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    glAttachShader(program, fs);
    glAttachShader(program, vs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;

}

void Shader::SetUniform4f(const string& name, float v1, float v2, float v3, float v4)
{
    GLCall(glUniform4f(GetUniformLocation(name), v1, v2, v3, v4));
}

void Shader::SetUniformMat4f(const string& name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1,GL_FALSE,&matrix[0][0]);
}

void Shader::SetUniform1i(const string& name, int value)
{
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

int Shader::GetUniformLocation(const string& name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];
    GLCall(int position = glGetUniformLocation(m_RendererID, name.c_str()));
    if (position == -1)
    {
        ASSERT(false);
        cout << "ERROR: Uniform Location " << name << "Does Not Exist" << endl;
    }
    else
        m_UniformLocationCache[name] = position;

    return position;
}
