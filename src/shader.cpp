#include <shaders.hpp>

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

    /* No livro, é dito que num pipeline gráfico, a saída de um shader é a entrada do próximo.
     * Nesse sentido, os dados que o vertex shader produz são os dados que o fragment shader recebe.
     * Por isso, solicitamos ao OpenGL que faça o 'link' dos shaders que criamos num Programa, que os
     * executará em sequência, passando a saída de um como entrada de outro.
     */
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

void Shader::use() {
    glUseProgram(this->id);
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