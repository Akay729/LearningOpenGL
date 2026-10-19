#pragma once

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

        void InitWindow();
        void InitGLAD();
        void MainLoop();
        void CleanUp();

        void CheckWindowCreation(GLFWwindow* window);
        void ProcessInput(GLFWwindow* window);
        
};