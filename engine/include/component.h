/*组件类，可以给Object的实例添加组件，以实现一些功能*/
#pragma once

#include <glm/glm.hpp>
#include <functional>

class Node;

class Component
{
  public:
    Component();
    virtual ~Component();
    // 逐帧调度器
    virtual void update();
};

// 鼠标事件回调函数
typedef std::function<void(glm::vec2, unsigned int button)> MouseEventCallback;
// 鼠标按钮
enum
{
    btn_left = 1<<0,
    btn_right = 1<<1,
    btn_mid = 1<<2
};
// 鼠标事件监听器
class MouseEventListener : public Component
{
  public:
    MouseEventListener();
    virtual ~MouseEventListener();
    virtual void update();

    // 当鼠标按下时
    MouseEventCallback onPress;
    // 当鼠标松开时
    MouseEventCallback onRelease;
    // 当鼠标移动时
    MouseEventCallback onMove;
  private:
    glm::vec2 lastPos;
    unsigned int lastBtn;
};

// 键盘事件回调函数
typedef std::function<void(int key, int scancode, int action, int mods)> KeyboardEventCallback;
// 键盘事件监听器
class KeyboardEventListener : public Component
{
  public:
    KeyboardEventListener();
    virtual ~KeyboardEventListener();
    KeyboardEventCallback callback;
};
