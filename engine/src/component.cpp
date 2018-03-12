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

void Component::updateLater()
{

}

// 鼠标事件监听器
MouseEventListener::MouseEventListener(Scene *scene)
{
    this->scene = scene;
    buttonCallback = [](int key, int action, int mods){return false;};
    moveCallback = [](vec2 pos){return false;};
    scrollCallback = [](vec2 offset){return false;};
    // 在鼠标事件监听列表中注册本监听器
    scene->mouseEventListeners.push_back(this);
    cout << "MouseEventistener [0x" << hex << this << "] signed in." << endl;
}

MouseEventListener::~MouseEventListener()
{
    // 从键盘监听列表中注销本监听器
    auto &listeners = scene->mouseEventListeners;
    for(auto iter = listeners.begin();iter!=listeners.end();++iter)
    {
        if(*(iter)==this)
        {
            listeners.erase(iter);
            cout << "MouseEventistener [0x" << hex << this << "] has been released." << endl;
            break;
        }
    }
}

KeyboardEventListener::KeyboardEventListener(Scene *scene)
{
    callback = [](int key, int scancode, int action, int mods){return false;};
    // 在键盘事件监听列表中注册本监听器
    scene->keyboardEventListeners.push_back(this);
    cout << "KeyBoardEventistener [0x" << hex << this << "] signed in." << endl;
}

KeyboardEventListener::~KeyboardEventListener()
{
    // 从键盘监听列表中注销本监听器
    auto &listeners = scene->keyboardEventListeners;
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
