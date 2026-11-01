#pragma once

#include <glad/glad.h>
#include <iostream>

//-- Shader Stuff

//@todo: Andrà tolto non appena si implementerà il sistema di shader completo
//VertexShader
inline const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 AColoror;\n"
    "out vec3 vertexColor;"
    "void main()\n"
    "{\n"
    " gl_Position = vec4(aPos, 1.0);\n"
    " vertexColor = AColoror;\n"
    "}\0";

//@todo: Andrà tolto non appena si implementerà il sistema di shader completo
//FragmentShader
inline const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 vertexColor;"
    "uniform vec4 shaderColor;" //è una gloabal variabile.
    "void main()\n"
    "{\n"
    //" FragColor = shaderColor;"
    " FragColor = vec4(vertexColor, 1.0);"
    "}\n\0";


class Shader
{
    public:
    
    static unsigned int CreateShader(unsigned int shaderType /*GLenum*/, const char* source /*the shader source*/);
    static unsigned int CreateShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);
    
    private:
    static void CheckShaderCompileError(unsigned int shader);
    static void CheckLinkingErrors(int shaderProgram);

};