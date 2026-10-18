#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int heigth);

// Dimensioni Finestra
const unsigned int WINDOW_W = 800;
const unsigned int WINDOW_H = 600;



int main()
{
	//Initializzazione e Configurazione
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //il tipo di profilo da usare di opengl

	GLFWwindow* window = glfwCreateWindow(WINDOW_W, WINDOW_H, "test window", NULL, NULL);
	if(window == NULL)
	{
		std::cerr << "Failed to create GLFW window...\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD\n";
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;

	}


	//Le prime 2 impostano le coridna dell'angolo in basso a sinistrea e le altre 2 la relativa largezza e altezza
	glViewport(0,0, WINDOW_W, WINDOW_H); 
	
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0; 
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0,0, width, height);
}
