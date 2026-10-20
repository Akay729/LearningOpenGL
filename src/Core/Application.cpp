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

    //VertexShader
    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
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

    //FragmentShader
    const char *fragmentShaderSource = "#version 330 core\n"
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

    //Le shader create non sono più necessarie dopo il linking, verrano eliminate appena accadrà il detach del shaderProgram
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    
    //VBO significa Vertex Buffer Object, serve per passare i dati alla GPU 
    //VAO significa Vertex Array Object, è un insime di attributi di vertici
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //Collega il VAO per primo e poi il VBO, in questo modo il VAO salverà le configurazioni del VBO
    glBindVertexArray(VAO);

    //Prende il buffer di vertici e lo passa alla GPU
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
   
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 );
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    //Copia i vertici nel buffer
    // Main loop code
    while (!glfwWindowShouldClose(m_window))
    {
        //Input
		ProcessInput(m_window);
		
		//Rendering
		glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

        //Draw triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

		//Check e chiama gli eventi poi swappa i buffer
		glfwPollEvents();
		glfwSwapBuffers(m_window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

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
