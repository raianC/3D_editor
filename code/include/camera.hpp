#pragma once

#include <glm/glm.hpp>
#include "scene.hpp"
#include <glm/gtc/matrix_transform.hpp>


class camera {
    
    private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    float yaw;
    float pitch;
    float speed;
    float sensitivity;

    public:
    camera(glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch);
    void processKeyboardInput(GLFWwindow* window, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset);
    glm::mat4 getViewMatrix();

};