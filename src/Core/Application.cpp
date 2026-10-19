#include <Application.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void MainApplication::Run()
{
    InitWindow();
    InitGLAD();
    MainLoop();
    CleanUp();
}


void MainApplication::InitWindow()
{
    // Window initialization code
    glfwInit();
	//versione e profilo di opengl da usare
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
	//il tipo di profilo da usare di opengl (ne ha 2 core o immidiate)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
    
	//Creazione Finestra con relativo check di errore
	m_window = glfwCreateWindow(WINDOW_W, WINDOW_H, "test window", NULL, NULL);
    CheckWindowCreation(m_window);

    glfwMakeContextCurrent(m_window);
	glfwSetFramebufferSizeCallback(m_window, FrammebufferSizeCallback);
}

void MainApplication::MainLoop()
{
    //@todo: Da cambiare
    glViewport(0,0, WINDOW_W, WINDOW_H);

    //VBO significa Vertex Buffer Object, serve per passare i dati alla GPU
    unsigned int vertexBuffer; 
    //Prende il buffer di vertici e lo passa alla GPU richiede un int che definisce il numero dei triangoli
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    //VertexShader
    const char *vertexShaderSource = "#version 460 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(GL_VERTEX_SHADER, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    //Check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED \n"
                << infoLog << std::endl;
    }

    const char *fragmentShaderSource = "#version 460 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    //Shader Program, Serve per linkare i vari shader e creare un programma di shader
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    //Check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram,512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED \n"
                << infoLog << std::endl;
    }

    // Main loop code
    while (!glfwWindowShouldClose(m_window))
    {
        //input
		ProcessInput(m_window);
		
		//Rendering



		glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//Check e chiama gli eventi poi swappa i buffer
		glfwPollEvents();
		glfwSwapBuffers(m_window);
    }
}

void MainApplication::CleanUp()
{
    // Cleanup code
    glfwDestroyWindow(m_window);

    glfwTerminate();
}

void MainApplication::InitGLAD()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        CleanUp();
        exit(-1);
    }
}

void MainApplication::CheckWindowCreation(GLFWwindow *window)
{
    if(window == NULL)
    {
        std::cerr << "Failed to create GLFW window...\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}

void MainApplication::ProcessInput(GLFWwindow *window)
{
    CheckWindowCreation(window);
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void MainApplication::FrammebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0,0, width, height);
}
