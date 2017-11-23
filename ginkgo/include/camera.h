#pragma once

#include <macros.h>
#include <glm/glm.hpp>
#include <node.h>

namespace ginkgo
{
    /// <summary>摄像机类</summary>
    /// <para>每一个场景都至少有一个摄像机，由相机我们可以得到视图矩阵和投影矩阵，从而对顶点进行变换。</para>
	class DLL Camera : public Node
	{
	public:
        /// <summary>构造一个摄像机</summary>
        /// <para>默认创建一个正交的投影阵，适用于2D场景。如果需要创建透视矩阵，可以在构造后对projectionMatrix重新赋值。</para>
        /// <param name="parent">父节点，通常是场景</param>
        /// <param name="position">摄像机位置</param>
        /// <param name="worldUp">世界坐标的上方向</param>
        /// <param name="yaw">摄像机的偏航角（左右方向），默认为-90.0f（朝前看，0.0f时是朝右的）</param>
        /// <param name="pitch">摄像机的俯仰角，默认为0（水平）</param>
		Camera(
            Node* parent,
			glm::vec3 position = glm::vec3(0.0f),
			glm::vec3 worldUp = glm::vec3(0.0f,1.0f,0.0f),
			float yaw = -90.0f,
			float pitch = 0.0f);
        /// <summary>获取视图矩阵</summary>
        /// <returns>返回4x4的视图矩阵</returns>
		glm::mat4 getViewMatrix();
        /// <summary>投影矩阵</summary>
        /// <returns>返回4x4的投影矩阵</returns>
		glm::mat4 projectionMatrix;
        /// <summary>更新摄像机的向量</summary>
        /// <para>在场景更新时调用，在改变了摄像机的位置和角度等属性之后，需要计算新的相关向量</para>
		void updateCameraVectors();
        /// <summary>获取视线方向（局部坐标系）</summary>
        /// <returns>返回摄像机的正向向量</returns>
		glm::vec3 getFront();
	protected:
        /// <summary>摄像机的正方向</summary>
		glm::vec3 front;
        /// <summary>摄像机的上方向</summary>
		glm::vec3 up;
        /// <summary>摄像机的右方向</summary>
		glm::vec3 right;
        /// <summary>世界坐标上方向</summary>
		glm::vec3 worldUp;
	};
}