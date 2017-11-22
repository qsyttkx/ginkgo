#pragma once

#include <macros.h>
#include <glm/glm.hpp>
#include <node.h>

namespace ginkgo
{
    /// <summary>�������</summary>
    /// <para>ÿһ��������������һ�����������������ǿ��Եõ���ͼ�����ͶӰ���󣬴Ӷ��Զ�����б任��</para>
	class DLL Camera : public Node
	{
	public:
        /// <summary>����һ�������</summary>
        /// <para>Ĭ�ϴ���һ��������ͶӰ��������2D�����������Ҫ����͸�Ӿ��󣬿����ڹ�����projectionMatrix���¸�ֵ��</para>
        /// <param name="parent">���ڵ㣬ͨ���ǳ���</param>
        /// <param name="position">�����λ��</param>
        /// <param name="worldUp">����������Ϸ���</param>
        /// <param name="yaw">�������ƫ���ǣ����ҷ��򣩣�Ĭ��Ϊ-90.0f����ǰ����0.0fʱ�ǳ��ҵģ�</param>
        /// <param name="pitch">������ĸ����ǣ�Ĭ��Ϊ0��ˮƽ��</param>
		Camera(
            Node* parent,
			glm::vec3 position = glm::vec3(0.0f),
			glm::vec3 worldUp = glm::vec3(0.0f,1.0f,0.0f),
			float yaw = -90.0f,
			float pitch = 0.0f);
        /// <summary>��ȡ��ͼ����</summary>
        /// <returns>����4x4����ͼ����</returns>
		glm::mat4 getViewMatrix();
        /// <summary>ͶӰ����</summary>
        /// <returns>����4x4��ͶӰ����</returns>
		glm::mat4 projectionMatrix;
        /// <summary>���������������</summary>
        /// <para>�ڳ�������ʱ���ã��ڸı����������λ�úͽǶȵ�����֮����Ҫ�����µ��������</para>
		void updateCameraVectors();
        /// <summary>��ȡ���߷��򣨾ֲ�����ϵ��</summary>
        /// <returns>�������������������</returns>
		glm::vec3 getFront();
	protected:
        /// <summary>�������������</summary>
		glm::vec3 front;
        /// <summary>��������Ϸ���</summary>
		glm::vec3 up;
        /// <summary>��������ҷ���</summary>
		glm::vec3 right;
        /// <summary>���������Ϸ���</summary>
		glm::vec3 worldUp;
	};
}