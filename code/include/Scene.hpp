//Scene.hpp

#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Mesh.hpp"
#include <iostream>
#include "camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Scene {
    private:
    const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;

        void main()
        {
            gl_Position = projection * view * model * vec4(aPos, 1.0);
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
    GLFWwindow* windowPtr = nullptr;

    // Variables de la souris et la caméra de la scène
    camera cam; 
    float lastX = 400.0f;
    float lastY = 300.0f;
    bool firstMouse = true;

    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

public:
    Scene();
    void window();
    void update();
    void draw(std::vector<HalfEdge*> halfEdges, GLFWwindow* window);
    GLFWwindow* getwindow();
    
    // Permet au callback statique d'accéder à la caméra de l'instance
    camera& getCamera() { return cam; }
};