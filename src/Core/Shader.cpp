#include "Shader.h"
#include <fstream>
#include <sstream>

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    //Check per i file di shader
    try
    {
        // apre i file di shader
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        // legge il buffer nell stream e lo assegna alle stringhe
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // chiude i file di shader
        vShaderFile.close();
        fShaderFile.close();

        // converte lo stream in stringhe
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure &e)
    {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    vertexShader = Shader::CreateShader(GL_VERTEX_SHADER, vShaderCode);
    fragmentShader = Shader::CreateShader(GL_FRAGMENT_SHADER, fShaderCode);
    ID = Shader::CreateShaderProgram(vertexShader, fragmentShader);

}

unsigned int Shader::CreateShader(unsigned int shaderType /*GLenum*/, const char *source)
{
    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    CheckShaderCompileError(shader);
    return shader;
}

unsigned int Shader::CreateShaderProgram(unsigned int vShader, unsigned int fShader)
{
    //Shader Program, Serve per linkare i vari shader e creare un programma di shader
    ID = glCreateProgram();
    glAttachShader(ID, vShader);
    glAttachShader(ID, fShader);
    glLinkProgram(ID);
    CheckLinkingErrors(ID);
    
    glDeleteShader(vShader);
    glDeleteShader(fShader);
    return ID;
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