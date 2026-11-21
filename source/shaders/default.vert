#version 460 core                           

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoords;

out vec2 v_TexCoords;

void main(void)                                 
{                              
    gl_Position = position;    
    v_TexCoords = texCoords;                          
}                                               
