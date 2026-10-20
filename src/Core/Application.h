#pragma once
#include <glad/glad.h>

const unsigned int WINDOW_W = 800;
const unsigned int WINDOW_H = 600;


//VertexShader
inline const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

//FragmentShader
inline const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

struct GLFWwindow;

class MainApplication
{
	public:
        
        void Run();
        
        static void FrammebufferSizeCallback(GLFWwindow* window, int width, int height);
		
    protected:
        GLFWwindow* m_window = nullptr;

        float vertices[12] = {
            0.f, 0.f, 0.0f, // bottom left
             0.5f, 0.0f, 0.0f, // bottom right
             0.5f,  0.5f, 0.0f  // top center
        };

        
        void InitWindow();
        void InitGLAD();
        void MainLoop();
        void CleanUp();

        void CheckWindowCreation(GLFWwindow* window);
        void ProcessInput(GLFWwindow* window);
        
};

class Shader
{
    public:
    
    GLuint CreateShader(GLenum shaderType, const char* source /*the shader source*/);
    void CreateShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);
    
    protected:
    void CheckShaderCompileError(unsigned int shader);
    void CheckLinkingErrors(int shaderProgram);





};
