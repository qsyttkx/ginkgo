#pragma once

#include <macros.h>
#include <glm/glm.hpp>
#include <node.h>

namespace ginkgo
{
	class DLL Camera : public Node
	{
	public:
		Camera(
			glm::vec3 position = glm::vec3(0.0f),
			glm::vec3 worldUp = glm::vec3(0.0f,1.0f,0.0f),
			float yaw = -90.0f,
			float pitch = 0.0f);
		glm::mat4 getViewMatrix();
		glm::mat4 projectionMatrix;
		void updateCameraVectors();
		glm::vec3 getFront();
	protected:
		glm::vec3 front;
		glm::vec3 up;
		glm::vec3 right;
		glm::vec3 worldUp;
		float yaw;
		float pitch;
		float zoom;
	};
}