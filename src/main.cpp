#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

    if(window == nullptr) {
        std::cerr << "" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, windowResizeCallback);
    gladLoadGL();

    glClearColor(0.5f, 0.1f, 0.6f, 1.0f);
    glViewport(0 , 0, 800, 600);

    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_CLEAR_VALUE);
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}