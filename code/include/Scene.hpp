//Scene.hpp

#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Mesh.hpp"
#include <iostream>

class Scene {
    private:
    const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;

        void main()
        {
            gl_Position = vec4(aPos, 1.0);
        }
    )";

    const char* fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;

        void main()
        {
            FragColor = vec4(1.0, 0.5, 0.2, 1.0);
        }
    )";
    
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    public:
    Scene();
    void window();
    void update();
    void draw(std::vector<HalfEdge*> halfEdges,GLFWwindow* window);
    

};