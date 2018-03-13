#include <button.h>
#include <ginkgo.h>

using namespace std;
using namespace glm;

Button::Button(Scene* scene, string normal, string pressed, string hover) : Sprite(normal)
{
    this->scene = scene;
    // 如果其他几个纹理没有设置则将就正常的用
    if (pressed == "")
        pressed = normal;
    if (hover == "")
        hover = normal;
    auto manager = ResourceManager::getInstance();
    texNormal = manager->getTexture(normal);
    texPressed = manager->getTexture(pressed);
    texHover = manager->getTexture(hover);

    isPressed = false;

    onClick = [](int, int) {};
    listener = new MouseEventListener(scene);
    listener->moveCallback = [=](vec2 pos) {
        if(!this->isEnabled)return false;// 如果鼠标处于非enabled的状态就不监听事件
        // 判断是否鼠标落在了按钮内
        if (checkMousePosition(pos))
        {
            if (isPressed)
            {
                // 设置按下纹理
                setTexture(texPressed);
            }
            else
            {
                // 设置悬停纹理
                setTexture(texHover);
            }
            return true;
        }
        else
        {
            // 设置正常纹理
            setTexture(texNormal);
            return false;
        }
    };

    listener->buttonCallback = [=](int button, int action, int mods) {
        if(!this->isEnabled)return false;// 如果鼠标处于非enabled的状态就不监听事件
        // 判断是否鼠标落在了按钮内
        vec2 pos = Game::getInstance()->getMousePosition();
        bool check = checkMousePosition(pos);
        if(action == GLFW_PRESS && check)
        {
            // 设置按下纹理
            setTexture(texPressed);
            isPressed = true;
            return true;
        }
        else if(action == GLFW_RELEASE && check)
        {
            // 触发事件
            onClick(button, mods);
            // 设置悬停纹理
            setTexture(texHover);
            isPressed = false;
            return true;
        }
        else if(action == GLFW_RELEASE && !check)
        {
            // 设置正常纹理
            setTexture(texNormal);
            isPressed = false;
            return false;
        }
    };

    // 添加监听器
    addComponent("mouseEventListener", listener);
    // 添加文本标签
    label = new Label();
    addChild(label);
}

// 设置文本
void Button::setText(std::string text)
{
    label->setText(text);
    // 居中对齐
    float xoff = -label->getContainSize().x * 0.5f;
    float yoff = -label->getContainSize().y * 0.15f;
    label->setPosition(xoff,yoff);
}
void Button::setText(std::string text, FontStyle style)
{
    label->setText(text, style);
    // 居中对齐
    float xoff = -label->getContainSize().x * 0.5f;
    float yoff = -label->getContainSize().y * 0.15f;
    label->setPosition(xoff,yoff);
}
void Button::setFontStyle(FontStyle style)
{
    label->setFontStyle(style);
    // 居中对齐
    float xoff = -label->getContainSize().x * 0.5f;
    float yoff = -label->getContainSize().y * 0.15f;
    label->setPosition(xoff,yoff);
}
// 获取文本
string Button::getText()
{
    return label->getText();
}

Button::~Button()
{
    delete (listener);
}

void Button::update()
{
    Sprite::update();
    // 将绑定的监听器放到最顶上，这样可以使得监听器的层次与按钮在场景上的层次一直（为了处理多个按钮叠加的情况）
    // 先从原来的位置去掉
    auto &listeners = scene->mouseEventListeners;
    for(auto iter = listeners.begin();iter!=listeners.end();++iter)
    {
        if(*(iter)==listener)
        {
            listeners.erase(iter);
            break;
        }
    }
    // 然后再加到顶上
    scene->mouseEventListeners.push_front(listener);
}

bool Button::checkMousePosition(vec2 pos)
{
    // 屏幕坐标系（鼠标）和世界坐标系的y轴是相反的
    pos.y = Game::getInstance()->getWindowSize().y - pos.y;

    // 计算按钮矩形四个顶点的位置
    vec4 leftup = globalTransform * model * vec4(-0.5f, 0.5f, 0.0f, 1.0f);
    vec4 leftdown = globalTransform * model * vec4(-0.5f, -0.5f, 0.0f, 1.0f);
    vec4 rightup = globalTransform * model * vec4(0.5f, 0.5f, 0.0f, 1.0f);
    vec4 rightdown = globalTransform * model * vec4(0.5f, -0.5f, 0.0f, 1.0f);

    // 计算是否落点到矩形内
    // 是否在上下两边之间
    vec3 upline = vec3(rightup.x - leftup.x, rightup.y - leftup.y, 0.0f);
    vec3 upToPos = vec3(pos.x - leftup.x, pos.y - leftup.y, 0.0f);
    vec3 cross1 = cross(upline, upToPos);
    vec3 downline = vec3(rightdown.x - leftdown.x, rightdown.y - leftdown.y, 0.0f);
    vec3 downToPos = vec3(pos.x - leftdown.x, pos.y - leftdown.y, 0.0f);
    vec3 cross2 = cross(downline, downToPos);
    bool flag1 = dot(cross1, cross2) <= 0.0f;
    // 是否在左右两边之间
    vec3 leftline = vec3(leftup.x - leftdown.x, leftup.y - leftdown.y, 0.0f);
    vec3 leftToPos = vec3(pos.x - leftdown.x, pos.y - leftdown.y, 0.0f);
    vec3 cross3 = cross(leftline, leftToPos);
    vec3 rightline = vec3(rightup.x - rightdown.x, rightup.y - rightdown.y, 0.0f);
    vec3 rightToPos = vec3(pos.x - rightdown.x, pos.y - rightdown.y, 0.0f);
    vec3 cross4 = cross(rightline, rightToPos);
    bool flag2 = dot(cross3, cross4) <= 0.0f;

    return flag1 && flag2;
}
