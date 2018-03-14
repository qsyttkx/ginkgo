#pragma once

#include <node.h>
#include <shader.h>

class Camera : public Node
{
  public:
    // 摄像机构造函数
    // 1摄像机位置
    // 2世界坐标的上方向
    // 3摄像机的偏航角（左右方向），默认为-90.0f（朝前看，0.0f时是朝右的）
    // 4摄像机的俯仰角，默认为0（水平）
    Camera(
        glm::vec3 position = glm::vec3(0.0f),
        glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = -90.0f,
        float pitch = 0.0f);
    ~Camera();

    //获取视图矩阵
    glm::mat4 getViewMatrix();
    //投影矩阵
    glm::mat4 projectionMatrix;
    //获取视线方向（局部坐标系）
    glm::vec3 getFront();

    //更新摄像机的向量
    //在场景更新时调用，在改变了摄像机的位置和角度等属性之后，需要计算新的相关向量
    void updateCameraVectors();

    // 给着色器设置投影矩阵和视图矩阵
    void setProjectionAndView(Shader* shader);
  protected:
    // 摄像机的正方向
    glm::vec3 front;
    // 摄像机的上方向
    glm::vec3 up;
    // 摄像机的右方向
    glm::vec3 right;
    // 世界坐标上方向
    glm::vec3 worldUp;
};
