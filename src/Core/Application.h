#pragma once

#include <vector>

const unsigned int WINDOW_W = 800;
const unsigned int WINDOW_H = 600;

struct GLFWwindow;

class MainApplication
{
	public:
        
        void Run();
        
        static void FrammebufferSizeCallback(GLFWwindow* window, int width, int height);
		
    protected:
        GLFWwindow* m_window = nullptr;

        /*
        // Basta dare i vertici per creare il triangolo senza ripetere i vertici
        // qua sevono solo i 4 vertici del quadrato
        float vertices[18] = {
            //First Triangle
            0.f, 0.f, 0.0f,     // bottom left
            0.5f, 0.0f, 0.0f,   // bottom right
            0.5f, 0.5f, 0.0f,   // top right
            0.0f, 0.5f, 0.0f,   // top left
            //Ex1
            -0.5f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.0f
            //
        };

        //Ho pesto tempo perchè gli avevo messi come float e non come unsigned int...
        unsigned int indicies[6] = {
            0,1,2,
            0,2,3
        };*/
        
        void InitWindow();
        void InitGLAD();
        void MainLoop();
        void CleanUp();

        void CheckWindowCreation(GLFWwindow* window);
        void ProcessInput(GLFWwindow* window);
        
};



//-- Shader Stuff

//@todo: Andrà tolto non appena si implementerà il sistema di shader completo
//VertexShader
inline const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

//@todo: Andrà tolto non appena si implementerà il sistema di shader completo
//FragmentShader
inline const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    " FragColor = vec4(.7f, 0.2f, 0.9f, 1.0f);\n"
    "}\n\0";


// Ex1
inline const char *fragmentShaderSource2 = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    " FragColor = vec4(.15f, 0.18f, 0.29f, 1.0f);\n"
    "}\n\0";
//





class Shader
{
    public:
    
    static unsigned int CreateShader(unsigned int shaderType /*GLenum*/, const char* source /*the shader source*/);
    static unsigned int CreateShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);
    
    private:
    static void CheckShaderCompileError(unsigned int shader);
    static void CheckLinkingErrors(int shaderProgram);

};



//-- Mesh Stuff
struct Vertex
{
    float position[3];
};

class Mesh
{
    private:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indicies;

        unsigned int VBO{}, VAO{}, EBO{};   
    
    public:

        Mesh(const std::vector<Vertex>& verts, const std::vector<unsigned int>& inds);
        ~Mesh();
       
        void SetUp(); 

        unsigned int GetVBO() {return VBO;};
        unsigned int GetVAO() {return VAO;};
        unsigned int GetEBO() {return EBO;};

        void DeleteMesh();

};