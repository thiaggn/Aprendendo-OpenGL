#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    unsigned int id;

    Shader(char *vertexPath, char *fragmentPath);

    void use();
    void set(std::string &variable_name, bool value) const;
    void set(std::string &variable_name, int value) const;
    void set(std::string &variable_name, float value) const;
};