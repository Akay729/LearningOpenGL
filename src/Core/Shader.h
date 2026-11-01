#pragma once

#include <glad/glad.h>
#include <iostream>

//-- Shader Stuff

class Shader
{
    public:

    unsigned int vertexShader;
    unsigned int fragmentShader;

    unsigned int ID;
    
    // Constructor per la shader, prende in input i percorsi dei file contenenti il codice sorgente degli shader
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader() { glDeleteProgram(ID); };
    
    unsigned int CreateShader(unsigned int shaderType /*GLenum*/, const char* source /*the shader source*/);
    unsigned int CreateShaderProgram(unsigned int vShader, unsigned int fShader);

    unsigned int GetID() { return ID;};
    void Use() { glUseProgram(ID);};

    void DeleteShaderProgram() { glDeleteProgram(ID); };

    private:

    static void CheckShaderCompileError(unsigned int shader);
    static void CheckLinkingErrors(int shaderProgram);

};