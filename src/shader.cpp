#include <shaders.hpp>
#include <GLFW/glfw3.hpp>

using std::string;
using std::ifstream;
using std::stringstream;

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    // Lê o arquivo do vertex e fragment shader
    string vertexCode, fragmentCode;
    ifstream vertexShaderFile, fragmentShaderFile;

    vertexShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    fragmentShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

    try
    {
        vertexShaderFile.open(vertexPath);
        fragmentShaderFile.open(fragmentPath);

        stringstream vertexShaderStream, fragmentShaderStream;
        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();

        fragmentShaderFile.close();
        vertexShaderFile.close();

        vertexCode = vertexShaderStream.str();
        fragmentCode = fragmentShaderStream.str();
    }
    catch (ifstream::failure &error)
    {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    const char *vertexShaderCode = vertexCode.c_str();
    const char *fragmentShaderCode = fragmentCode.c_str();

    unsigned int vertexShader, fragmentShader;
    int success;
    char infoLog[512];

    // Inicializa e compila o vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n " << infoLog << std::endl;
    }

    // Inicializa e compila o fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n " << infoLog << std::endl;
    }

    this->id = glCreateProgram();
    glAttachShader(this->id, vertexShader);
    glAttachShader(this->id, fragmentShader);
    glLinkProgram(this->id);
    glGetProgramiv(id, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(this->id, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() const {
    glUseProgram(this->id);
//
//    auto timeValue = (float)glfwGetTime();
//    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
//    int vertexColorLocation = glGetUniformLocation(this->id, "ourColor");
//    glUniform4f(vertexColorLocation,  0.0f, greenValue, 0.0f, 1.0f);

    /*Note that finding the uniform location does not require you to use the shader program first, but updating a
    uniform does require you to first use the program (by calling glUseProgram), because it sets the
    uniform on the currently active shader program.*/

}

void Shader::set(const string &variable_name, int value) const {
    glUniform1i(glGetUniformLocation(this->id, variable_name.c_str()), value);
}

void Shader::set(const string &variable_name, bool value) const {
    glUniform1i(glGetUniformLocation(this->id, variable_name.c_str()), (int)value);
}

void Shader::set(const string &variable_name, float value) const {
    glUniform1f(glGetUniformLocation(this->id, variable_name.c_str()), value);
}

// Pesquisar pq passar "alguma string" para qualquer um dos metodos set só funciona
// se o parametro for <const string &variable_name> ou <const string variable_name> ou <string variable_name>