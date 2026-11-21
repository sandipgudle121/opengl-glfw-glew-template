#pragma once

#include <GL/glew.h> // Must be included before GLFW/OpenGL headers.
#include <GLFW/glfw3.h>
#include <string>

using namespace std;

class Texture
{
    private:
    unsigned int m_RendererId;
    string m_FilePath;
    unsigned char *m_LocalBuffer;
    int m_Width, m_Height, m_BitsPerPixel;

    public:
    Texture(const string &path);
    ~Texture();

    void Bind(unsigned int slot=0) const;
    void Unbind() const;

    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; } 
};