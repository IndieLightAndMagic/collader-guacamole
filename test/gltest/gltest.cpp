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



#include <SDLWrapper/sdlwrapper.h>
#include <ShaderMan/shdr.h>
#include <collader/collader.h>

/* A simple function that will read a file into an allocated char pointer buffer */
GTech::Program GetShaders();

struct VtxEntry {

    std::vector<unsigned int>    vao{};
    std::vector<unsigned int>   ebos{};
    std::vector<unsigned int>   vbos{};

}; 


std::shared_ptr<VtxEntry> GetVtxs(const GTech::Mesh& mesh){
    
    /* Get Vtxs */
    auto meshdata            = mesh.floatVector.data();
    auto meshdatasize        = mesh.floatVector.size() * sizeof(float);
    auto vtxentry            = std::make_shared<VtxEntry>();

    /* Get the number of "triangle-composites" */ 
    auto nTriangleComposites = mesh.triangleArray.size();

    /* For each <triangles/> collada element generate a vao */
    vtxentry->vao.reserve(nTriangleComposites);
    glGenVertexArrays(nTriangleComposites, vtxentry->vao.data());


    for (auto index = 0; index < nTriangleComposites; ++index){

        unsigned int vbo, ebo;
        auto pTriangleCompositeRaw = mesh.triangleArray[index].get();
        auto indexdata             = pTriangleCompositeRaw->indexArray.data();
        auto indexdatasize         = pTriangleCompositeRaw->indexArray.size() * sizeof(unsigned int);

        glBindVertexArray(vtxentry->vao[index]);

        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);
        
        vtxentry->ebos.push_back(ebo);
        vtxentry->vbos.push_back(vbo);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, meshdatasize, meshdata, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexdatasize, indexdata, GL_STATIC_DRAW);

        for (auto& input : pTriangleCompositeRaw->meshTrianglesInput){
            
            /* <input/> */
            unsigned int vertexAttributeId;
            
            auto offset      = input.offset;
            auto pOffset     = &meshdata[offset];
            auto source      = input.source;
            auto map         = mesh.meshSourceMap;
            auto pMeshSource = map[source];
            auto stride      = pMeshSource->stride;

            if (input.semanticType == GTech::MeshTrianglesInput::DataType::TEXCOORD){
                vertexAttributeId = 2;
            } else if (input.semanticType == GTech::MeshTrianglesInput::DataType::NORMAL){
                vertexAttributeId = 1;
            } else if (input.semanticType == GTech::MeshTrianglesInput::DataType::VERTEX){
                vertexAttributeId = 0;
            }

            glVertexAttribPointer(vertexAttributeId, stride, GL_FLOAT, GL_FALSE, stride*sizeof(GLfloat), pOffset);
            glEnableVertexAttribArray(vertexAttributeId);

        }
        
    }

    return vtxentry;
}
void drawscene(const GTech::Scene& rScene)
{
    
    /* Get GPU Program */
    auto shaderprogram = GetShaders();
    shaderprogram.use();
    
    std::map<std::string, std::shared_ptr<VtxEntry>> vtxs{};

    for (auto& meshname_mesh : rScene.meshes){

        auto meshname = meshname_mesh.first;
        auto mesh     = meshname_mesh.second;
        
    }

    
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

GTech::Scene GetScene(std::string path){

    tinyxml2::XMLDocument doc;
    auto result = doc.LoadFile(path.c_str());

    if ( result != tinyxml2::XML_SUCCESS){

        std::cout << "Returning an empty Scene.... Couldn't load collada file.... \n";
        return GTech::Scene{};
    
    } else {

        std::cout << "Ok scene file was successfully loaded.... \n"; 

    }

    GTech::ColladaVisitor visitor;
    auto pVisitor = &visitor;
    doc.Accept(pVisitor);
    auto aScene = visitor.GetScene();

    std::cout << "Scene name is: " << aScene.name << std::endl;

    return aScene;
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
    
    auto daePath = std::string{RESOURCES_DIR} + std::string{"/simple.dae"};
    auto scene   = GetScene(daePath);

    for (auto&nodekey_nodeptr : scene.nodes){

        auto nodeptr = nodekey_nodeptr.second;
        std::cout << "Node: " << nodeptr->name << " -- ";
        if (nodeptr->nodeType == GTech::Node::NodeType::MESH) std::cout << "MESH";
        if (nodeptr->nodeType == GTech::Node::NodeType::LIGHT) std::cout << "LIGHT";
        if (nodeptr->nodeType == GTech::Node::NodeType::CAMERA) std::cout << "CAMERA";
        std::cout << std::endl;

        if (nodeptr->nodeType == GTech::Node::NodeType::MESH){

            auto meshptr = std::dynamic_pointer_cast<GTech::Mesh>(nodeptr);
        } 

    }

    /* Call our function that performs opengl operations */
    drawscene(scene);

    /* Delete our opengl context, destroy our window, and shutdown SDL */
    destroywindow();

    return 0;
}