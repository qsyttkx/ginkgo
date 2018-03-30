#pragma once
#include <ginkgo.h>
#include <iostream>
#include <string>

using namespace glm;
using namespace std;

class Test : public Scene
{
public:
    Test(Scene* menu, string titleString)
    {
        menuScene = menu;
        // 设置白色背景
        setBackgroundColor(vec4(1.0f, 1.0f, 1.0f, 1.0f));
        // 获取游戏窗口的尺寸(画面的尺寸，不包含标题栏和边框)
        glm::vec2 wSize = Game::getInstance()->getWindowSize();
        // 初始化按钮
        btn_back = new Button(this, "btn_normal", "btn_pressed", "btn_hover");
        addChild(btn_back);
        btn_back->setText("返回", FontStyle(18));
        btn_back->onClick = [=](int key, int mods) {
            // 返回菜单
            Game::getInstance()->replaceScene(menu);
        };
        // 为节点设置位置的z值可以影响渲染次序，z值越高的越先渲染
        btn_back->setPosition(wSize.x - 75.0f, 50.0f, 1);
        // 初始化标题标签
        title = new Label(titleString, FontStyle(32));
        addChild(title);
        title->setPosition((wSize.x - title->getContainSize().x) / 2, wSize.y - 50.0f, 1.0f);
    }

    virtual ~Test()
    {
        // 设置回白色背景
        setBackgroundColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    }

    virtual void update()
    {
        Scene::update();
    }

private:
    // 菜单场景
    Scene* menuScene;
    // 返回按钮
    Button *btn_back;
    // 标题标签
    Label *title;
};
