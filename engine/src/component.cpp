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
    buttonCallback = [](int key, int action, int mods){};
    moveCallback = [](vec2 pos){};
    scrollCallback = [](vec2 offset){};
    // 在鼠标事件监听列表中注册本监听器
    Game::getInstance()->mouseEventListeners.push_back(this);
    cout << "MouseEventistener [0x" << hex << this << "] signed in." << endl;
}

MouseEventListener::~MouseEventListener()
{
    // 从键盘监听列表中注销本监听器
    auto listeners = Game::getInstance()->mouseEventListeners;
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
