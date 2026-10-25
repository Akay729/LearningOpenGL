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

    GLuint vertexShader = Shader::CreateShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = Shader::CreateShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    GLuint shaderProgram = Shader::CreateShaderProgram(vertexShader, fragmentShader);

    //Ex1
    GLuint secondShaderProgram = Shader::CreateShaderProgram(
        vertexShader,
        Shader::CreateShader(GL_FRAGMENT_SHADER, fragmentShaderSource2)
    );
    //
    
    //VBO significa Vertex Buffer Object, serve per passare i dati alla GPU 
    //VAO significa Vertex Array Object, è un insime di attributi di vertici
    unsigned int VAO_1, VBO_1, EBO_1;
    glGenVertexArrays(1, &VAO_1);
    glGenBuffers(1, &VBO_1);
    glGenBuffers(1, &EBO_1);

    //Collega il VAO per primo e poi il VBO, in questo modo il VAO salverà le configurazioni del VBO
    glBindVertexArray(VAO_1);

    //Prende il buffer di vertici e lo passa alla GPU
    glBindBuffer(GL_ARRAY_BUFFER, VBO_1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
   
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_1); // quasi usa GL_ELEMENT_ARRAY_BUFFER
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);// quasi usa GL_ELEMENT_ARRAY_BUFFER

    //Configura il modo in cui OpenGL deve interpretare i dati del buffer
    // 0 -> è l'indice del attributo che deve equivalere alla location del vertex shader
    // 3 -> è il numero di componenti per vertice (x, y, z)
    // GL_FLOAT -> è il tipo di dato dei componenti
    // GL_FALSE -> indica se i dati devono essere normalizzati o meno
    // 3 * sizeof(float) -> è la distanza tra i vertici consecutivi nel buffer (stride)
    // (void*)0 -> è l'offset del primo componente del primo vertice nel buffer 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 ); // (void*)0 è un puntatore vuoto nullo
    glEnableVertexAttribArray(0);


    //unbind il VBO e il VAO per evitare modifiche accidentali
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Main loop code
    while (!glfwWindowShouldClose(m_window))
    {
        //Input
		ProcessInput(m_window);
		
		//Rendering
		glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        
        //Draw first triangle 
        glBindVertexArray(VAO_1);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
        
        //Ex1
        glUseProgram(secondShaderProgram);
        glDrawArrays(GL_TRIANGLES, 4, 3);
        //

		//Check e chiama gli eventi poi swappa i buffer
		glfwPollEvents();
		glfwSwapBuffers(m_window);
    } 

    
    glDeleteVertexArrays(1, &VAO_1);
    glDeleteBuffers(1, &VBO_1);
    glDeleteBuffers(1, &EBO_1);
    glDeleteProgram(shaderProgram);

    //Ex 1
    glDeleteProgram(secondShaderProgram);
    //
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
    
    //FILL e WIREFRAME
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //GL_LINE per wireframe
    }
    if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {  
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //GL_FILL per fill
    }
}

void MainApplication::FrammebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0,0, width, height);
}


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

void Mesh::InitMesh()
{
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //Collega il VAO per primo e poi il VBO, in questo modo il VAO salverà le configurazioni del VBO
    glBindVertexArray(VAO);

    //Prende il buffer di vertici e lo passa alla GPU
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
   
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // quasi usa GL_ELEMENT_ARRAY_BUFFER
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);// quasi usa GL_ELEMENT_ARRAY_BUFFER

    //Configura il modo in cui OpenGL deve interpretare i dati del buffer
    // 0 -> è l'indice del attributo che deve equivalere alla location del vertex shader
    // 3 -> è il numero di componenti per vertice (x, y, z)
    // GL_FLOAT -> è il tipo di dato dei componenti
    // GL_FALSE -> indica se i dati devono essere normalizzati o meno
    // 3 * sizeof(float) -> è la distanza tra i vertici consecutivi nel buffer (stride)
    // (void*)0 -> è l'offset del primo componente del primo vertice nel buffer 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 ); // (void*)0 è un puntatore vuoto nullo
    glEnableVertexAttribArray(0);


    //unbind il VBO e il VAO per evitare modifiche accidentali
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::SetVerticesNumber(float vertices)
{
}

void Mesh::SetIndices(float IndexArray[])
{
}
