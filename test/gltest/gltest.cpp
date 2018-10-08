#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>
#include <vector>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#else 
#include <OpenGL/gl.h>
#endif /*__APPLE__*/


#include <SDLWrapper/sdlwrapper.h>
#include <ShaderMan/shdr.h>

/* A simple function that will read a file into an allocated char pointer buffer */
std::vector<char> filetobuf(const char *file)
{

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
GTech::Program InitScene() {

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

void drawscene()
{
    int i; /* Simple iterator */
    GLuint vao, vbo[2]; /* Create handles for our Vertex Array Object and two Vertex Buffer Objects */
    int isCompiled_VS, isCompiled_FS;
    int IsLinked;
    int maxLength;
    char *vertexInfoLog;
    char *fragmentInfoLog;
    char *shaderProgramInfoLog;

    /* We're going to create a simple diamond made from lines */
    const GLfloat diamond[4][2] = {
    {  0.0,  1.0  }, /* Top point */
    {  1.0,  0.0  }, /* Right point */
    {  0.0, -1.0  }, /* Bottom point */
    { -1.0,  0.0  } }; /* Left point */

    const GLfloat colors[4][3] = {
    {  1.0,  0.0,  0.0  }, /* Red */
    {  0.0,  1.0,  0.0  }, /* Green */
    {  0.0,  0.0,  1.0  }, /* Blue */
    {  1.0,  1.0,  1.0  } }; /* White */

    /* These pointers will receive the contents of our shader source code files */
    
    /* These are handles used to reference the shaders */
    GLuint vertexshader, fragmentshader;

    /* Allocate and assign a Vertex Array Object to our handle */
    glGenVertexArrays(1, &vao);

    /* Bind our Vertex Array Object as the current used object */
    glBindVertexArray(vao);

    /* Allocate and assign two Vertex Buffer Objects to our handle */
    glGenBuffers(2, vbo);

    /* Bind our first VBO as being the active buffer and storing vertex attributes (coordinates) */
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

    /* Copy the vertex data from diamond to our buffer */
    /* 8 * sizeof(GLfloat) is the size of the diamond array, since it contains 8 GLfloat values */
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), diamond, GL_STATIC_DRAW);

    /* Specify that our coordinate data is going into attribute index 0, and contains two floats per vertex */
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    /* Enable attribute index 0 as being used */
    glEnableVertexAttribArray(0);

    /* Bind our second VBO as being the active buffer and storing vertex attributes (colors) */
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

    /* Copy the color data from colors to our buffer */
    /* 12 * sizeof(GLfloat) is the size of the colors array, since it contains 12 GLfloat values */
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), colors, GL_STATIC_DRAW);

    /* Specify that our color data is going into attribute index 1, and contains three floats per vertex */
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    /* Enable attribute index 1 as being used */
    glEnableVertexAttribArray(1);

    /* Get GPU Program */
    auto shaderprogram = InitScene();
    shaderprogram.use();
    
    

    
    /* Loop our display increasing the number of shown vertexes each time.
     * Start with 2 vertexes (a line) and increase to 3 (a triangle) and 4 (a diamond) */
    for (i=2; i <= 4; i++)
    {
        /* Make our background black */
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Invoke glDrawArrays telling that our data is a line loop and we want to draw 2-4 vertexes */
        glDrawArrays(GL_LINE_LOOP, 0, i);

        /* Swap our buffers to make our changes visible */
        GTech::SDLGlSwapWindow();

        /* Sleep for 2 seconds */
        SDL_Delay(2000);
    }

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

    //Load Shaders.
    InitScene();

    /* Call our function that performs opengl operations */
    drawscene();

    /* Delete our opengl context, destroy our window, and shutdown SDL */
    destroywindow();

    return 0;
}