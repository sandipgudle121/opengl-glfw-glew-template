#include <GL/glew.h> // Must be included before GLFW/OpenGL headers.
#include <GLFW/glfw3.h>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include <cstdio>

#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")

static FILE *logFile = nullptr;

int main()
{
    fopen_s(&logFile, "log.txt", "w");
    if (!glfwInit())
    {
        if (logFile)
            fprintf(logFile, "GLFW initialization failed.\n");
        return -1;
    }

    // The supplied shaders target GLSL 4.60 core.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Sandip Sham Gudle", nullptr, nullptr);
    if (!window)
    {
        if (logFile)
            fprintf(logFile, "Failed to create the GLFW window.\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        if (logFile)
            fprintf(logFile, "GLEW initialization failed.\n");
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
    glGetError(); // GLEW can generate a harmless GL_INVALID_ENUM in core mode.

    const float positions[] = {
        -0.5f,  0.5f, 0.0f, 1.0f,
         0.5f,  0.5f, 1.0f, 1.0f,
         0.5f, -0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f
    };

    const unsigned int indices[] = {0, 1, 2, 2, 3, 0};
    {
        Shader shader("source/shaders/default.vert", "source/shaders/default.frag");
        if (!shader.IsValid())
        {
            if (logFile)
                fprintf(logFile, "Shader program creation failed.\n");
        }
        else
        {
            VertexArray vertexArray;
            vertexArray.Bind();

            VertexBuffer vertexBuffer(positions, sizeof(positions));

            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<const void *>(2 * sizeof(float)));
            glEnableVertexAttribArray(1);

            IndexBuffer indexBuffer(indices, 6);

            Texture texture("resource/textures/anime_collage.jpg");
            vertexArray.Unbind();

            if (logFile)
                fprintf(logFile, "Program started successfully.\n");

            while (!glfwWindowShouldClose(window))
            {
                if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                    glfwSetWindowShouldClose(window, GLFW_TRUE);

                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                shader.Bind();
                shader.SetUniform1i("u_Texture", 0);
                texture.Bind(0);
                vertexArray.Bind();
                glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr);

                glfwSwapBuffers(window);
                glfwPollEvents();
            }
        }
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    if (logFile)
    {
        fprintf(logFile, "Program ended successfully.\n");
        fclose(logFile);
    }
    return 0;
}
