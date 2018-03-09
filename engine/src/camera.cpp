#include <ginkgo.h>
#include <camera.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

Camera::Camera(vec3 position, vec3 worldUp, float yaw, float pitch)
{
    this->setPosition(position);
    this->worldUp = worldUp;
    this->setRotation(glm::radians(pitch), glm::radians(yaw), 0.0f);
    updateCameraVectors();

    vec2 wSize = Game::getInstance()->getWindowSize();
    projectionMatrix = ortho(0.0f, wSize.x, 0.0f, wSize.y, 0.1f, wSize.y / 0.414f + 1000.0f);
}

Camera::~Camera()
{
}

mat4 Camera::getViewMatrix()
{
    vec3 pos = this->getPosition3();
    return lookAt(pos, pos + front, up);
}

vec3 Camera::getFront()
{
    return front;
}

void Camera::updateCameraVectors()
{
    vec3 rot = this->getRotation3();
    // 计算新的前向向量
    glm::vec3 front;
    front.x = cos(rot.y) * cos(rot.x);
    front.y = sin(rot.x);
    front.z = sin(rot.y) * cos(rot.x);
    this->front = glm::normalize(front);
    // 计算右和上方向的向量
    right = glm::normalize(glm::cross(this->front, worldUp));
    up = glm::normalize(glm::cross(right, this->front));
}

void Camera::setProjectionAndView(Shader &shader)
{
    shader.use();
    shader.setMat4("projection", projectionMatrix);
    shader.setMat4("view", getViewMatrix());
}
