// Scene.cpp
#pragma once
#include "Scene.hpp"


Scene::Scene() {
    // Constructor implementation
}

void Scene::window(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "3D Editor", nullptr, nullptr);

    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    
    glfwSetFramebufferSizeCallback(
        window,
        framebuffer_size_callback
    );


}

void Scene::draw(std::vector<HalfEdge*> halfEdges,GLFWwindow* window) {
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(
        vertexShader,
        1,
        &vertexShaderSource,
        nullptr
    );

    glCompileShader(vertexShader);

    // Vérification compilation
    int success;
    char infoLog[512];

    glGetShaderiv(
        vertexShader,
        GL_COMPILE_STATUS,
        &success
    );

    if (!success)
    {
        glGetShaderInfoLog(
            vertexShader,
            512,
            nullptr,
            infoLog
        );

        std::cerr << "Erreur vertex shader :\n"
                  << infoLog << std::endl;
    }

    unsigned int fragmentShader =
        glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(
        fragmentShader,
        1,
        &fragmentShaderSource,
        nullptr
    );

    glCompileShader(fragmentShader);

    glGetShaderiv(
        fragmentShader,
        GL_COMPILE_STATUS,
        &success
    );

    if (!success)
    {
        glGetShaderInfoLog(
            fragmentShader,
            512,
            nullptr,
            infoLog
        );

        std::cerr << "Erreur fragment shader :\n"
                  << infoLog << std::endl;
    }

    unsigned int shaderProgram =
        glCreateProgram();

    glAttachShader(
        shaderProgram,
        vertexShader
    );

    glAttachShader(
        shaderProgram,
        fragmentShader
    );

    glLinkProgram(shaderProgram);

    glGetProgramiv(
        shaderProgram,
        GL_LINK_STATUS,
        &success
    );

    if (!success)
    {
        glGetProgramInfoLog(
            shaderProgram,
            512,
            nullptr,
            infoLog
        );

        std::cerr << "Erreur linking shader :\n"
                  << infoLog << std::endl;
    }

    // Les shaders individuels ne sont plus nécessaires
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    // VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // VAO
    glBindVertexArray(VAO);

    // VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(halfEdges) * halfEdges.size(),
        halfEdges.data(),
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        // Fond
        glClearColor(
            0.1f,
            0.1f,
            0.1f,
            1.0f
        );

        glClear(GL_COLOR_BUFFER_BIT);


        // Utiliser les shaders
        glUseProgram(shaderProgram);

        // Taille des points
        glPointSize(0.5);

        // VAO
        glBindVertexArray(VAO);

        // Dessiner les 5 points
        glDrawArrays(
            GL_POINTS,
            0,
            static_cast<GLsizei>(halfEdges.size())
        );


        // Afficher
        glfwSwapBuffers(window);

        // Événements
        glfwPollEvents();
    }
}

void Scene::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}