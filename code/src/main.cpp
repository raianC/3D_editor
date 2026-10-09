// main.cpp
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Loader.hpp"
#include "PLYLoader.hpp"
#include "ObjLoader.hpp"

void PrintMesh(Loader& loader, const std::string& filename) {
    loader.LoadFile(filename);
    const auto& points = loader.GetPoints();
    const auto& faces = loader.GetFaces();

    for (const auto& point : points) {
        std::cout << "Point: ";
        for (const auto& coord : point) {
            std::cout << coord << " ";
        }
        std::cout << std::endl;
    }
    for (const auto& face : faces) {
        std::cout << "Face: ";
        for (const auto& index : face) {
            std::cout << index << " ";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char* argv[]) {
    PlyLoader plyLoader;

    PrintMesh(plyLoader, "3DModel/Cube.ply");
// --------------------------------------------------
// Shaders
// --------------------------------------------------

const char* vertexShaderSource = R"(
#version 330 core

layout (location = 0) in vec3 position;

void main()
{
    gl_Position = vec4(position, 1.0);
}
)";

const char* fragmentShaderSource = R"(
#version 330 core

out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
)";

// --------------------------------------------------
// Callback fenêtre
// --------------------------------------------------

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// --------------------------------------------------
// Main
// --------------------------------------------------

int main()
{
    // GLFW
    if (!glfwInit())
    {
        std::cerr << "Erreur GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(
        800,
        600,
        "Test OpenGL",
        nullptr,
        nullptr
    );

    if (!window)
    {
        std::cerr << "Erreur creation fenetre\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(
        window,
        framebuffer_size_callback
    );

    // GLAD
    if (!gladLoadGLLoader(
        (GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Erreur GLAD\n";
        return -1;
    }

    std::cout << "OpenGL : "
              << glGetString(GL_VERSION)
              << std::endl;


    // ==================================================
    // VERTEX SHADER
    // ==================================================

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


    // ==================================================
    // FRAGMENT SHADER
    // ==================================================

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


    // ==================================================
    // PROGRAMME SHADER
    // ==================================================

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


    // ==================================================
    // POINTS
    // ==================================================

    float points[] =
    {
        -0.7f,  0.5f, 0.0f,
         0.0f,  0.7f, 0.0f,
         0.7f,  0.5f, 0.0f,
        -0.4f, -0.4f, 0.0f,
         0.4f, -0.4f, 0.0f
    };


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
        sizeof(points),
        points,
        GL_STATIC_DRAW
    );

    // Position
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);


    // ==================================================
    // BOUCLE
    // ==================================================

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
        glPointSize(20.0f);

        // VAO
        glBindVertexArray(VAO);

        // Dessiner les 5 points
        glDrawArrays(
            GL_POINTS,
            0,
            5
        );


        // Afficher
        glfwSwapBuffers(window);

        // Événements
        glfwPollEvents();
    }


    // ==================================================
    // NETTOYAGE
    // ==================================================

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();

    return 0;
}