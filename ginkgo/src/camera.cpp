#define EXPORT
#include <macros.h>
#include <camera.h>
#include <glm/gtc/matrix_transform.hpp>
#include <ginkgo.h>

using namespace ginkgo;
using namespace glm;

Camera::Camera(Node* parent, vec3 position, vec3 worldUp, float yaw, float pitch) :Node(parent)
{
	this->position = position;
	this->worldUp = worldUp;
	this->rotation.y = yaw;
	this->rotation.x = pitch;
	updateCameraVectors();

	// 默认创建一个正交的投影阵
	float width = (float)Game::getConfigurations().width;
	float height = (float)Game::getConfigurations().height;
	projectionMatrix = ortho(0.0f, width, 0.0f, height, 0.1f, Game::getConfigurations().height / 0.414f + 1000.0f);
	//projectionMatrix = perspective(radians(45.0f), 640.0f / 480.0f, 0.1f, 1000.0f);
}

mat4 Camera::getViewMatrix()
{
	return lookAt(position, position + front, up);
}

vec3 Camera::getFront()
{
	return front;
}

void Camera::updateCameraVectors()
{
	// 计算新的前向向量
	glm::vec3 front;
	front.x = cos(glm::radians(rotation.y))*cos(glm::radians(rotation.x));
	front.y = sin(glm::radians(rotation.x));
	front.z = sin(glm::radians(rotation.y))*cos(glm::radians(rotation.x));
	this->front = glm::normalize(front);
	// 计算右和上方向的向量
	right = glm::normalize(glm::cross(this->front, worldUp));
	up = glm::normalize(glm::cross(right, this->front));
}

