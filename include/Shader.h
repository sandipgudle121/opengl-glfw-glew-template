#pragma once
#include <string>
using namespace std;

class Shader
{
private:
    unsigned int m_RenderId;

public:
    Shader(const std::string& vertexFilepath, const std::string& fragmentFilepath);
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    void Bind() const;
    void Unbind() const;
    bool IsValid() const { return m_RenderId != 0; }

    void SetUniform1i(const string &name, int value) const;
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) const;

private:
    static std::string ReadFromFile(const std::string& filepath);
    static unsigned int CompileShader(unsigned int type, const std::string& filepath);
    int GetUniformLocation(const std::string& name) const;
};
