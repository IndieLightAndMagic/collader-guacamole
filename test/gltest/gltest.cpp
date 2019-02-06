#include <iostream>
#include <utility>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>


#include <GLFW/glfw3.h>

#include <collader/collader.h>
#include <ShaderMan/shdr.h>



GTech::Program GetShaders() {

    auto vtxShaderSrc = GTech::ShaderSource("../gltest.vert");
    auto vtxShader    = GTech::Shader(&vtxShaderSrc, GL_VERTEX_SHADER);
    
    auto frgShaderSrc = GTech::ShaderSource("../gltest.frag");
    auto frgShader    = GTech::Shader(&frgShaderSrc, GL_FRAGMENT_SHADER);

    auto program = GTech::Program();
    program.pushShader(&vtxShader);
    program.pushShader(&frgShader);

    program.link();

    auto programIsLinked = program.isLinked();

    return program; 
}

struct App{
	
	bool m_valid{false};

    App(){

        auto result = glfwInit();
        if (!result) return;
        glfwSetErrorCallback(App::ErrorCB);
        glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
		glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 5 );
		glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
		//glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );

        auto pWindow = glfwCreateWindow(800, 600, "Some Title", nullptr, nullptr);
        if (!pWindow){
        	std::cout << "FATAL: Error Creating Window" << std::endl;
        }
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

    auto daePathResource = std::string{"../resources/simple.dae"} + std::string{"/Cube"};



    return 0;
}