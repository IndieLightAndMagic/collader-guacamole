#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ShaderMan/shdr.h>






struct TheScene {

    unsigned int vbo, vao;
    static float vertices[];
    void SetupGeometry();
    TheScene();
};