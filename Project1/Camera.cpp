#include "Camera.h"

Camera::Camera() {
    std::cout << "test2" << std::endl;
    view = glm::lookAt(
        glm::vec3(0.0, 1.0, 8.0),  // eye
        glm::vec3(0.0, 0.5, 0.0),  // center
        glm::vec3(0.0, 1.0, 0.0));  // up

    projection = glm::perspective(
        glm::radians(65.0f),
        1.0f * 800 / 600, 0.1f,
        20.0f);

    rotateX = 0.5;
    translateY = -1.5f;
    //translateY = 0.5f;
    //translateZ = -4.5f;
}


Camera::Camera(const int WIDTH, const int HEIGHT) {
    std::cout << "test2" << std::endl;
    view = glm::lookAt(
        glm::vec3(0.0, 1.0, 8.0),  // eye
        glm::vec3(0.0, 0.5, 0.0),  // center
        glm::vec3(0.0, 1.0, 0.0));  // up

    projection = glm::perspective(
        glm::radians(45.0f),
        1.0f * WIDTH / HEIGHT, 0.1f,
        20.0f);
}
Camera::Camera(glm::mat4 view, glm::mat4 projection) {
    this->view = view;
    this->projection = projection;
}

void Camera::Forward() {
    if (rotateY > 0.79f && rotateY < 2.37f)
        translateX -= 0.1f;
    else if (rotateY > 2.37f && rotateY < 3.94f)
        translateZ -= 0.1f;
    else if (rotateY > 3.94f && rotateY < 5.52f)
        translateX += 0.1f;
    else
        translateZ += 0.1f;
}
void Camera::Backwards() {
    if (rotateY > 0.79f && rotateY < 2.37f)
        translateX += 0.1f;
    else if (rotateY > 2.37f && rotateY < 3.94f)
        translateZ += 0.1f;
    else if (rotateY > 3.94f && rotateY < 5.52f)
        translateX -= 0.1f;
    else
        translateZ -= 0.1f;
}
void Camera::Left() {
    if (rotateY > 0.79f && rotateY < 2.37f)
        translateZ += 0.1f;
    else if (rotateY > 2.37f && rotateY < 3.94f)
        translateX -= 0.1f;
    else if (rotateY > 3.94f && rotateY < 5.52f)
        translateZ -= 0.1f;
    else
        translateX += 0.1f;
}
void Camera::Right() {
    if (rotateY > 0.79f && rotateY < 2.37f)
        translateZ -= 0.1f;
    else if (rotateY > 2.37f && rotateY < 3.94f)
        translateX += 0.1f;
    else if (rotateY > 3.94f && rotateY < 5.52f)
        translateZ += 0.1f;
    else
        translateX -= 0.1f;
}

void Camera::LookDown(){
    if (rotateX > 6.2f && rotateX < 6.4f)
        rotateX -= 6.3f;
    rotateX += 0.1f;
}
void Camera::LookUp(){
    if (rotateX > -0.1f && rotateX < 0.1f)
        rotateX += 6.3f;
    rotateX -= 0.1f;
}
void Camera::LookLeft(){
    if (rotateY > -0.1f && rotateY < 0.1f)
        rotateY += 6.3f;
    rotateY -= 0.1f;
}
void Camera::LookRight(){
    if (rotateY > 6.2f && rotateY < 6.4f)
        rotateY -= 6.3f;
    rotateY += 0.1f;
}

void Camera::Up() {
    translateY = 0.1f;
}

void Camera::Down() {
    translateY = -0.1f;
}

void Camera::Update() {
    view = glm::translate(view, glm::vec3(translateX, translateY, translateZ));

    //projection matrix
    projection = glm::rotate(projection, rotateY, glm::vec3(0.0, 1.0, 0.0));
    projection = glm::rotate(projection, rotateX, glm::vec3(1.0, 0.0, 0.0));
    //projection = glm::rotate(projection, rotateZ, glm::vec3(0.0, 0.0, 1.0));

    rotateX = 0;
    rotateY = 0;
    rotateZ = 0;
    translateX = 0;
    translateY = 0;
    translateZ = 0;
}