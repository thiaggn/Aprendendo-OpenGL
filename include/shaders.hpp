#pragma once
#include <glad/glad.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    unsigned int id;

    Shader(const char *vertexPath, const char *fragmentPath);

    void use() const;
    void set(const std::string &variable_name, bool value) const;
    void set(const std::string &variable_name, int value) const;
    void set(const std::string &variable_name, float value) const;
};