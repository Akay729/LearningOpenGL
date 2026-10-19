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