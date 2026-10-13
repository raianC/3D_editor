// Scene.cpp
#include "Scene.hpp"


Scene::Scene() 
    : cam(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f) {
    // Constructor implementation
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
std::vector<float> vertices;
vertices.reserve(halfEdges.size() * 6); // 2 sommets par half-edge * 3 coordonnées

for (HalfEdge* he : halfEdges)
{
    if (he == nullptr)
        continue;

    // Récupération de l'origine et de la cible de la demi-arête
    // (Adaptez "Origin()" si la méthode s'appelle getSource() ou autre dans votre code)
    Vertex* origin = he->Twin()->Target();
    Vertex* target = he->Target();

    if (origin == nullptr || target == nullptr)
        continue;

    std::array<float, 3> posOrg = origin->getPosition();
    std::array<float, 3> posTar = target->getPosition();

    // 1. Premier point de la ligne (Départ)
    vertices.push_back(posOrg[0]);
    vertices.push_back(posOrg[1]);
    vertices.push_back(posOrg[2]);

    // 2. Second point de la ligne (Arrivée)
    vertices.push_back(posTar[0]);
    vertices.push_back(posTar[1]);
    vertices.push_back(posTar[2]);
}

glBindBuffer(GL_ARRAY_BUFFER, VBO);

glBufferData(
    GL_ARRAY_BUFFER,
    vertices.size() * sizeof(float),
    vertices.data(),
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

   camera cam(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Entrées clavier pour bouger la caméra principale de la scène
        cam.processKeyboardInput(window, deltaTime);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = cam.getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
        unsigned int viewLoc  = glGetUniformLocation(shaderProgram, "view");
        unsigned int projLoc  = glGetUniformLocation(shaderProgram, "projection");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc,  1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc,  1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO);
        glLineWidth(2.0f); // Épaisseur des lignes du cube

        glDrawArrays(
            GL_LINES, // On passe en mode lignes par paires de sommets
            0,
            static_cast<GLsizei>(vertices.size() / 3)
        );

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Scene::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Scene::update() {
    // Update logic for the scene
}


GLFWwindow* Scene::getwindow() {
    return windowPtr;
}

void Scene::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void Scene::mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    std::cout << "Souris bougee : " << xposIn << ", " << yposIn << std::endl; // <-- Ligne de test

    Scene* sceneInstance = static_cast<Scene*>(glfwGetWindowUserPointer(window));
    if (!sceneInstance) return;

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (sceneInstance->firstMouse) {
        sceneInstance->lastX = xpos;
        sceneInstance->lastY = ypos;
        sceneInstance->firstMouse = false;
    }

    float xoffset = xpos - sceneInstance->lastX;
    float yoffset = sceneInstance->lastY - ypos; 
    sceneInstance->lastX = xpos;
    sceneInstance->lastY = ypos;

    // Transmet le mouvement à la vraie caméra de la scène
    sceneInstance->cam.processMouseMovement(xoffset, yoffset);
}

void Scene::window(){
    std::cout << "Debug 1: Avant glfwInit" << std::endl;
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return;
    }
    
    std::cout << "Debug 2: Avant window hints" << std::endl;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    std::cout << "Debug 3: Avant glfwCreateWindow" << std::endl;
    windowPtr = glfwCreateWindow(800, 600, "3D Editor", nullptr, nullptr);

    if (!windowPtr) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    
    std::cout << "Debug 4.1: Avant set window user pointer" << std::endl;
    glfwSetWindowUserPointer(windowPtr, this);

    std::cout << "Debug 4.2: Avant set key callback" << std::endl;
    glfwSetKeyCallback(windowPtr, key_callback);

    std::cout << "Debug 4.3: Avant set cursor pos callback" << std::endl;
    glfwSetCursorPosCallback(windowPtr, mouse_callback);

    std::cout << "Debug 4.4: Avant set input mode" << std::endl;
    //glfwSetInputMode(windowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    std::cout << "Debug 4.5: Avant make context current" << std::endl;
    glfwMakeContextCurrent(windowPtr);

    std::cout << "Debug 4.6: Avant enable depth test" << std::endl;
    

    std::cout << "Debug 5: Avant gladLoadGLLoader" << std::endl;
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        glfwDestroyWindow(windowPtr);
        glfwTerminate();
        return;
    }

    glEnable(GL_DEPTH_TEST);
    std::cout << "Debug 6: Tout est initialise !" << std::endl;
}