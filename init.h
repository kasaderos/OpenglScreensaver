#include "common.h"
#include "global.h"
#define GLFW_DLL
#include <GLFW/glfw3.h>

GLFWwindow*  window;
namespace Init{
    int initGL()
    {
        int res = 0;
        //грузим функции opengl через glad
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize OpenGL context" << std::endl;
            return -1;
        }

        std::cout << "Vendor: "   << glGetString(GL_VENDOR) << std::endl;
        std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
        std::cout << "Version: "  << glGetString(GL_VERSION) << std::endl;
        std::cout << "GLSL: "     << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

        return 0;
    }

    int init(){
        if(!glfwInit())
            return -1;

        //запрашиваем контекст opengl версии 3.3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE); 
        window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL basic sample", nullptr, nullptr);
        if (window == nullptr)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        
        glfwMakeContextCurrent(window); 
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        glfwSetWindowSizeCallback(window, windowResize);	
        if(initGL() != 0) 
            return -1;
        
    //Reset any OpenGL errors which could be present for some reason
        GLenum gl_error = glGetError();
        while (gl_error != GL_NO_ERROR)
            gl_error = glGetError();        
        return 0;
    }

}