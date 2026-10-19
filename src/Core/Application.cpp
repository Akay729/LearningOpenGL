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
