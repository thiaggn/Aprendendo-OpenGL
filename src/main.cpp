#include <iostream>
#include <glad/glad.hpp>
#include <GLFW/glfw3.hpp>
#include <shaders.hpp>

void windowResizeCallback(GLFWwindow *window, int height, int width) {
    glViewport(0, 0, width, height);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(
    800,
    600,
    "DragonSlayer",
    nullptr,
    nullptr
    );

    if(window == nullptr)
    {
        std::cerr << "" << std::endl;
        glfwTerminate();
        return -1;
    }


    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, windowResizeCallback);
    gladLoadGL();

    glClearColor(0.5f, 0.1f, 0.6f, 1.0f);
    glViewport(0 , 0, 800, 600);

    char fragmentShaderPath[] = R"(D:\Thiago\DragonSlayer\resources\fragmentShader.glsl)";
    char vertexShaderPath[] = R"(D:\Thiago\DragonSlayer\resources\vertexShader.glsl)";

    Shader shader(vertexShaderPath, fragmentShaderPath);

    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
    };

    /*  VBO é o buffer onde se armazena vértices.
     *  |> ACESSO AOS DADOS:
     *      DRAW: O usuário escreverá dados no buffer, mas não os lê.
     *          É útil, para como o nome sugere, desenhar. O usuário está escrevendo dados, mas apenas o OpenGL os está lendo.
     *      READ: O usuário não escreverá dados no buffer, mas os lerá.
     *          É comum ser usado quando um buffer é usado como um destino para os comandos do OpenGL.
     *      COPY: O usuário nem escreverá dados no buffem, nem os lerá.
     *          É usado quando um buffer passa dados de um lugar no OpenGL para outro, como uma imagem.
     *
     *  |> FREQUENCIA DE MODIFICACAO DOS DADOS:
     *      STATIC: Dados são escritos no buffer uma única vez
     *      DYNAMIC: Dados são escritos no buffer ocasionalmente
     *      STREAM: Dados são alterados no buffer a cada loop de renderização
     */
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(VBO, GL_ARRAY_BUFFER);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_CLEAR_VALUE);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}