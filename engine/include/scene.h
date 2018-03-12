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

    // 设置背景色
    void setBackgroundColor(glm::vec4 bg);
    // 获取背景色
    glm::vec4 getBackgroundColor();

    // 键盘事件监听器列表
    std::list<KeyboardEventListener*> keyboardEventListeners;
    // 鼠标时间监听器列表
    std::list<MouseEventListener*> mouseEventListeners;
protected:
    // 默认相机
    Camera* defaultCamera;
    // 背景色(glClearColor)
    glm::vec4 backgroundColor;
    ImGuiRenderer* imGuiRenderer;
};
