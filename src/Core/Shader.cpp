#include "Shader.h"

unsigned int Shader::CreateShader(unsigned int shaderType /*GLenum*/, const char* source)
{
    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    CheckShaderCompileError(shader);
    return shader;
}

unsigned int Shader::CreateShaderProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
    //Shader Program, Serve per linkare i vari shader e creare un programma di shader
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    CheckLinkingErrors(shaderProgram);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}

void Shader::CheckShaderCompileError(unsigned int shader)
{
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {   
        //Dovrei far crashaare il programma
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED \n"
        << infoLog << std::endl;
    }
}

void Shader::CheckLinkingErrors(int shaderProgram)
{
    //Check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram,512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED \n"
                << infoLog << std::endl;
    }
}