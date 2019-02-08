#include <iostream>
#include <utility>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>


#include <glad/glad.h>
#include <GLFW/glfw3.h>


struct App{
	
	bool m_valid{false};

    App(){

        glfwSetErrorCallback(App::ErrorCB);
        
        auto result = glfwInit();
        if (!result) return;

        glfwWindowHint( GLFW_RESIZABLE, GLFW_FALSE );
        glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
		glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 2 );
		glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
		glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );

        auto pWindow = glfwCreateWindow(800, 600, "Wolfenray", nullptr, nullptr);
        if (!pWindow){
            glfwTerminate();
        	std::cout << "FATAL: Error Creating Window" << std::endl;
            std::exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(pWindow);
        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    }

    static void ErrorCB(int errorNumber, const char* errorDesc){

    	std::cout << "ERROR NO: " << errorNumber << std::endl;
    	std::cout << "ERROR Description: " << errorDesc << std::endl;

    }
    void Shutdown(){
    	glfwTerminate();
    }

};

 


/* Our program's entry point */
int main(int argc, char *argv[])
{
    App app;
    std::cout << "GL SHADING LANGUAGE VERSION: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << " " << glGetString(GL_VERSION) << std::endl; 
    std::cout << "Resource directory: " << RESOURCES_DIR << std::endl; 



    return 0;
}