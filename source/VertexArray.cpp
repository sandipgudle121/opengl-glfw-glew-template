#include <GL/glew.h>
#include "VertexArray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_RenderId);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_RenderId);
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_RenderId);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}
