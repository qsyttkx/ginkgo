#pragma once

#include <node.h>
#include <camera.h>

class ImGuiRenderer:public Component
{
public:
    ImGuiRenderer();
    virtual ~ImGuiRenderer();
    virtual void updateLater();
};

class Scene : public Node
{
public:
    // 构建一个场景
    Scene();
    // 析构场景
    virtual ~Scene();
    virtual void update();

    void setBackgroundColor(glm::vec4 bg);
    glm::vec4 getBackgroundColor();
protected:
    // 默认相机
    Camera* defaultCamera;
    // 背景色(glClearColor)
    glm::vec4 backgroundColor;
    ImGuiRenderer* imGuiRenderer;
};
