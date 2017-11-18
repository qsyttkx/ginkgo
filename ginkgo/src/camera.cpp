#include <camera.h>
#include <glm/gtc/matrix_transform.hpp>
#include <ginkgo.h>

using namespace ginkgo;
using namespace glm;

Camera::Camera(vec3 position, vec3 worldUp, float yaw, float pitch) :Node()
{
	this->position = position;
	this->worldUp = worldUp;
	this->yaw = yaw;
	this->pitch = pitch;
	updateCameraVectors();

	float halfwidth = Game::getConfigurations().width*0.5f;
	float halfheight = Game::getConfigurations().height*0.5f;
	// Ĭ�ϴ���һ��������ͶӰ��
	projectionMatrix = ortho(-halfwidth, halfwidth, -halfheight, halfheight, 0.1f, 5000.0f);
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
	// �����µ�ǰ������
	glm::vec3 front;
	front.x = cos(glm::radians(yaw))*cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw))*cos(glm::radians(pitch));
	this->front = glm::normalize(front);
	// �����Һ��Ϸ��������
	right = glm::normalize(glm::cross(this->front, worldUp));
	up = glm::normalize(glm::cross(right, this->front));
}

