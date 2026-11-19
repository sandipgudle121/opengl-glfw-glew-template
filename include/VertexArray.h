#pragma once

class VertexArray
{
private:
    unsigned int m_RenderId;

public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void Unbind() const;
};
