#include <component.h>
#include <ginkgo.h>

using namespace std;
using namespace glm;

Component::Component()
{
}

Component::~Component()
{
}

void Component::update()
{
}

// 鼠标事件监听器
MouseEventListener::MouseEventListener()
{
    onPress = [](vec2, unsigned int) {};
    onRelease = [](vec2, unsigned int) {};
    onMove = [](vec2, unsigned int) {};

    lastPos = Game::getInstance()->getMousePosition();
    lastBtn = 0;
}

MouseEventListener::~MouseEventListener()
{
}

void MouseEventListener::update()
{
    GLFWwindow *w = Game::getInstance()->getGLFWwindow();
    unsigned int left = glfwGetMouseButton(w, GLFW_MOUSE_BUTTON_LEFT);
    unsigned int right = glfwGetMouseButton(w, GLFW_MOUSE_BUTTON_RIGHT);
    unsigned int mid = glfwGetMouseButton(w, GLFW_MOUSE_BUTTON_MIDDLE);

    vec2 pos = Game::getInstance()->getMousePosition();
    unsigned int btn = left | (right << 1) | (mid << 2);

    // 触发移动事件
    if (pos.x - lastPos.x != 0 || pos.y - lastPos.y != 0)
    {
        onMove(pos, btn);
    }

    // 触发按下事件
    if ((left) && !(lastBtn & btn_left))
    {
        onPress(pos, btn_left);
    }
    if ((right) && !(lastBtn & btn_right))
    {
        onPress(pos, btn_right);
    }
    if ((mid) && !(lastBtn & btn_mid))
    {
        onPress(pos, btn_mid);
    }

    // 触发松开事件
    if (!(left) && (lastBtn & btn_left))
    {
        onRelease(pos, btn_left);
    }
    if (!(right) && (lastBtn & btn_right))
    {
        onRelease(pos, btn_right);
    }
    if (!(mid) && (lastBtn & btn_mid))
    {
        onRelease(pos, btn_mid);
    }

    lastPos = pos;
    lastBtn = btn;
}

KeyboardEventListener::KeyboardEventListener()
{
    callback = [](int key, int scancode, int action, int mods){};
    // 在键盘事件监听列表中注册本监听器
    Game::getInstance()->keyboardEventListeners.push_back(this);
    cout << "KeyBoardEventistener [0x" << hex << this << "] signed in." << endl;
}

KeyboardEventListener::~KeyboardEventListener()
{
    // 从键盘监听列表中注销本监听器
    auto listeners = Game::getInstance()->keyboardEventListeners;
    for(auto iter = listeners.begin();iter!=listeners.end();++iter)
    {
        if(*(iter)==this)
        {
            listeners.erase(iter);
            cout << "KeyBoardEventistener [0x" << hex << this << "] has been released." << endl;
            break;
        }
    }
}
