#include <iostream>
#include <utility>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#else 
#include <OpenGL/gl.h>
#endif /*__APPLE__*/


#include <AssetManager/assetmanager.h>
#include <ECS/Entity/entitymanager.h>
#include <ECS/System/sceneresourcer.h>
#include <ECS/System/glRendering.h>

#include <SDLWrapper/sdlwrapper.h>
#include <ShaderMan/shdr.h>
#include <collader/collader.h>




void drawscene(const GTech::Scene& rScene)
{
    



    
    /* Loop our display increasing the number of shown vertexes each time.
     * Start with 2 vertexes (a line) and increase to 3 (a triangle) and 4 (a diamond) */
    //for (i=2; i <= 4; i++)
    //{
        /* Make our background black */
    //  glClearColor(0.0, 0.0, 0.0, 1.0);
    //  glClear(GL_COLOR_BUFFER_BIT);

        /* Invoke glDrawArrays telling that our data is a line loop and we want to draw 2-4 vertexes */
    //  glDrawArrays(GL_LINE_LOOP, 0, i);

        /* Swap our buffers to make our changes visible */
    //  GTech::SDLGlSwapWindow();

        /* Sleep for 2 seconds */
    //  SDL_Delay(2000);
    //}

    /* Cleanup all the things we bound and allocated */
    //glUseProgram(0);
    //glDisableVertexAttribArray(0);
    //glDisableVertexAttribArray(1);
    //glDetachShader(shaderprogram, vertexshader);
    //glDetachShader(shaderprogram, fragmentshader);
    //glDeleteProgram(shaderprogram);
    //glDeleteShader(vertexshader);
    //glDeleteShader(fragmentshader);
    //glDeleteBuffers(2, vbo);
    //glDeleteVertexArrays(1, &vao);

}
void PrintShader(std::string msg, std::vector<char> buffer) {

    std::cout << msg <<  ":" <<  std::endl;
    for (auto pAux = buffer.data(); *pAux; ++pAux){
        std::cout << *pAux;
    }
    std::cout << std::endl;
}
void ErrorMessage(std::string msg) {

    std::cout << ">>>>>>>>" << std::endl << msg <<  "<<<<<<<<<" <<  std::endl;
}

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
std::vector<char> filetobuf(const char *file){

    FILE *fptr;
    long length;

    fptr = fopen(file, "rb"); /* Open file for reading */
    
    if (!fptr) /* Return NULL on failure */
        return std::vector<char>{};

    fseek(fptr, 0, SEEK_END); /* Seek to the end of the file */
    length = ftell(fptr); /* Find out how many bytes into the file we are */
    
    auto buffer = std::vector<char>{};
    buffer.reserve(length+1);
        
    fseek(fptr, 0, SEEK_SET); /* Go back to the beginning of the file */
    for (auto idx = 0; idx < length; ++idx){
        auto buf = char{}, *pbuf = &buf;
        fread(pbuf, 1, 1, fptr); /* Read the contents of the file in to the buffer */
        buffer.push_back(buf);
    }
    fclose(fptr); /* Close the file */
    buffer.data()[length] = 0;


    return buffer; /* Return the buffer */
}


void destroywindow()
{

    GTech::SDLDestroyWindow();
    GTech::SDLQuit();

}

/* Our program's entry point */
int main(int argc, char *argv[])
{
    GTech::SDLInitialization();
    std::cout << "GL SHADING LANGUAGE VERSION: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << " " << glGetString(GL_VERSION) << std::endl; 
    std::cout << "Resource directory: " << RESOURCES_DIR << std::endl; 

    auto daePathResource = std::string{"../resources/simple.dae"} + std::string{"/Cube"};

    auto resourcemanager = GTech::ResourceManager::GetInstance();
    auto cube_id = resourcemanager.Load(daePathResource);

    /* Delete our opengl context, destroy our window, and shutdown SDL */
    destroywindow();

    return 0;
}