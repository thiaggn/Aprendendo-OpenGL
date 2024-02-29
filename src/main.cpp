#include <iostream>
#include <glad/glad.hpp>
#include <GLFW/glfw3.hpp>
#include <shaders.hpp>

void windowResizeCallback(GLFWwindow *window, int height, int width) {
    glViewport(0, 0, width, height);
}

int main() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
#endif

    // glfw: window creation
    // ---------------------

    GLFWwindow *window = glfwCreateWindow(
            800,
            600,
            "DragonSlayer",
            nullptr,
            nullptr
    );

    if (window == nullptr) {
        std::cerr << "" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, windowResizeCallback);

    // glad: load all opengl function pointers
    // ---------------------------------------

    gladLoadGL();

    // build and compile our shader program
    // ------------------------------------

    char fragmentShaderPath[] = R"(D:\Thiago\DragonSlayer\resources\fragmentShader.glsl)";
    char vertexShaderPath[] = R"(D:\Thiago\DragonSlayer\resources\vertexShader.glsl)";
    Shader shader(vertexShaderPath, fragmentShaderPath);

    // set up vertex data and buffers; configure vertex attributes
    // -----------------------------------------------------------

    float vertices[] = {
            -0.5f, -0.5f, 0.0f,     // left
            0.5f, -0.5f, 0.0f,     // right
            0.0f, 0.5f, 0.0f      // top
    };


    glClearColor(0.5f, 0.1f, 0.6f, 1.0f);
    glViewport(0, 0, 800, 600);

    // bind the VAO first, then bind and set the vertex buffers, and then configure vertex attributes
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(VBO, GL_ARRAY_BUFFER);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void *) 1);
    glEnableVertexAttribArray(0);


    glBindVertexArray(VAO);

    while (!glfwWindowShouldClose(window)) {
        // render
        // ------

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // glBindVertexArray(0); // no need to unbind it every time

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}