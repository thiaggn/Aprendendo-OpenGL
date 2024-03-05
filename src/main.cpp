#include <iostream>
#include <glad/glad.hpp>
#include <GLFW/glfw3.hpp>
#include <shaders.hpp>


void resize(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "DragonSlayer", nullptr, nullptr);

    if (window == nullptr) {
        std::cerr << "ERROR:GLFW:WINDOW_CREATION" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resize);

    gladLoadGL();
    glViewport(0, 0, 800, 600);

    char vertex_shader_path[] = R"(D:\Thiago\DragonSlayer\resources\vertexShader.glsl)";
    char o_fragment_shader_path[] = R"(D:\Thiago\DragonSlayer\resources\frag_shader_orange.glsl)";
    Shader shader1(vertex_shader_path, o_fragment_shader_path);

    unsigned int VAOs[2], VBOs[2];

    // Primeiro triangulo
    glGenVertexArrays(1, VAOs);
    glGenBuffers(1, VBOs);

    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);

    float vertices1[]{
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.01f,
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glClearColor(0.3f, 0.1f, 0.7f, 1.0f);
    
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        shader1.use();
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}