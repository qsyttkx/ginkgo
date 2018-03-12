#pragma once
#include <ginkgo.h>
#include <iostream>

using namespace glm;
using namespace std;

class SceneWelcome;

class Test01 : public Scene
{
public:
    // 菜单场景
    Scene* menuScene;
    // 返回按钮
    Button *btn_back;
    // 标题标签
    Label *title;


    bool show_demo_window;
    bool show_another_window;
    vec4 clear_color;

    Test01(Scene* menu);

    virtual ~Test01()
    {
    }

    virtual void update();
};
