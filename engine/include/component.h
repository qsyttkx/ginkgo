/*组件类，可以给Object的实例添加组件，以实现一些功能*/
#pragma once

#include <glm/glm.hpp>
#include <functional>

class Node;
class Scene;

class Component
{
  public:
    Component();
    virtual ~Component();
    // 逐帧调度器，在绑定节点遍历时为前序
    virtual void update();
    // 逐帧调度器，在绑定节点遍历为后后序
    virtual void updateLater();
};

// 鼠标按钮回调函数
typedef std::function<bool(int button, int action, int mods)> MouseButtonCallback;
// 鼠标移动回调函数
typedef std::function<bool(glm::vec2 pos)> MouseMoveCallback;
// 鼠标滚轮回调函数
typedef std::function<bool(glm::vec2 offset)> MouseScrollCallback;
// 鼠标事件监听器
class MouseEventListener : public Component
{
  public:
    MouseEventListener(Scene *scene);
    virtual ~MouseEventListener();
    MouseButtonCallback buttonCallback;
    MouseMoveCallback moveCallback;
    MouseScrollCallback scrollCallback;
private:
    Scene *scene;
};

// 键盘事件回调函数
typedef std::function<bool(int key, int scancode, int action, int mods)> KeyboardEventCallback;
// 键盘事件监听器
class KeyboardEventListener : public Component
{
  public:
    KeyboardEventListener(Scene *scene);
    virtual ~KeyboardEventListener();
    KeyboardEventCallback callback;
private:
    Scene *scene;
};
