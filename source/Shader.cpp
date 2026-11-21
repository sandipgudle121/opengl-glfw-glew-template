#include <GL/glew.h>

#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(const std::string& vertexFilepath, const std::string& fragmentFilepath) : m_RenderId(0)
{
    const unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexFilepath);
    const unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentFilepath);

    if (vertexShader == 0 || fragmentShader == 0)
    {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return;
    }

    m_RenderId = glCreateProgram();
    glAttachShader(m_RenderId, vertexShader);
    glAttachShader(m_RenderId, fragmentShader);
    glLinkProgram(m_RenderId);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    int linked = GL_FALSE;
    glGetProgramiv(m_RenderId, GL_LINK_STATUS, &linked);
    if (linked == GL_TRUE)
        return;

    char log[1024]{};
    glGetProgramInfoLog(m_RenderId, sizeof(log), nullptr, log);
    std::cerr << "Shader program linking failed:\n" << log << '\n';
    glDeleteProgram(m_RenderId);
    m_RenderId = 0;
}

Shader::~Shader()
{
    if (m_RenderId != 0)
        glDeleteProgram(m_RenderId);
}

void Shader::Bind() const
{
    glUseProgram(m_RenderId);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) const
{
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniform1i(const string &name, int value) const
{
    glUniform1i(GetUniformLocation(name), value);
}

std::string Shader::ReadFromFile(const std::string& filepath)
{
    std::ifstream file(filepath);
    if (!file)
    {
        std::cerr << "Could not open shader file: " << filepath << '\n';
        return {};
    }

    std::ostringstream contents;
    contents << file.rdbuf();
    return contents.str();
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& filepath)
{
    const std::string source = ReadFromFile(filepath);
    if (source.empty())
        return 0;

    const GLuint shader = glCreateShader(type);
    const char* sourcePointer = source.c_str();
    glShaderSource(shader, 1, &sourcePointer, nullptr);
    glCompileShader(shader);

    int compiled = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_TRUE)
        return shader;

    char log[1024]{};
    glGetShaderInfoLog(shader, sizeof(log), nullptr, log);
    std::cerr << "Shader compilation failed (" << filepath << "):\n" << log << '\n';
    glDeleteShader(shader);
    return 0;
}

int Shader::GetUniformLocation(const std::string& name) const
{
    const int location = glGetUniformLocation(m_RenderId, name.c_str());
    if (location == -1)
        std::cerr << "Uniform not found or inactive: " << name << '\n';
    return location;
}
