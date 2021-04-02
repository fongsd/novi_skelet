//
// Created by dusan on 4/2/21.
//

#ifndef SKELET_SHADER_H
#define SKELET_SHADER_H

#include <fstream>
#include <sstream>
#include "rg/Error.h"

std::string readFileContents(std::string path) {
    std::ifstream in(path);
    std::stringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}

class Shader
{
    int m_id;
public:
    Shader(std::string vertexShaderPath, std::string fragmentShaderPath)
    {
        std::string vsString = readFileContents(vertexShaderPath);
        ASSERT(!vsString.empty(), "vs string is empty!");
        const char *vertexShaderSource = vsString.c_str();
        int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

        int rez = 0;
        glCompileShader(vertexShader);
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &rez);

        if (!rez)
        {
            std::cout<<"failed to compile vertex shader"<<std::endl;
            glfwTerminate();
        }
        std::string fsString = readFileContents(fragmentShaderPath);
        ASSERT(!fsString.empty(), "framgent shader is empty!");
        const char * fragmentShaderSource = fsString.c_str();
        int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

        rez = 0;
        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &rez);

        if (!rez)
        {
            std::cout<<"failed to compile fragment shader"<<std::endl;
            glfwTerminate();
        }
        unsigned int shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &rez);

        if (!rez)
        {
            std::cout<<"failed to link shader program"<<std::endl;
            glfwTerminate();
        }
        m_id = shaderProgram;
    }

    void use()
    {
        ASSERT(m_id > 0, "shader program deleted!");
        glUseProgram(m_id);
    }

    void setUniform4f(std::string name, double d, double d1, double d2, double d3) {
        int id = glGetUniformLocation(m_id, name.c_str());
        glUniform4f(id, d, d1, d2, d3);
    }
};

#endif //SKELET_SHADER_H
