#pragma once

#include <macros.h>
#include <glm/glm.hpp>
#include <node.h>

namespace ginkgo
{
    //摄像机类
    //每一个场景都至少有一个摄像机，由相机我们可以得到视图矩阵和投影矩阵，从而对顶点进行变换。
	class DLL Camera : public Node
	{
	public:
        //构造一个摄像机
        //默认创建一个正交的投影阵，适用于2D场景。如果需要创建透视矩阵，可以在构造后对projectionMatrix重新赋值。
        //父节点，通常是场景
        //摄像机位置
        //世界坐标的上方向
        //摄像机的偏航角（左右方向），默认为-90.0f（朝前看，0.0f时是朝右的）
        //摄像机的俯仰角，默认为0（水平）
		Camera(
            Node* parent,
			glm::vec3 position = glm::vec3(0.0f),
			glm::vec3 worldUp = glm::vec3(0.0f,1.0f,0.0f),
			float yaw = -90.0f,
			float pitch = 0.0f);
        //获取视图矩阵
        //返回4x4的视图矩阵
		glm::mat4 getViewMatrix();
        //投影矩阵
        //返回4x4的投影矩阵
		glm::mat4 projectionMatrix;
        //更新摄像机的向量
        //在场景更新时调用，在改变了摄像机的位置和角度等属性之后，需要计算新的相关向量
		void updateCameraVectors();
        //获取视线方向（局部坐标系）
        //返回摄像机的正向向量
		glm::vec3 getFront();
	protected:
        //摄像机的正方向
		glm::vec3 front;
        //摄像机的上方向
		glm::vec3 up;
        //摄像机的右方向
		glm::vec3 right;
        //世界坐标上方向
		glm::vec3 worldUp;
	};
}