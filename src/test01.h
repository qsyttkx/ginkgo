#pragma once
#include <ginkgo.h>
#include <iostream>
#include "test.h"

using namespace glm;
using namespace std;

class SceneWelcome;

class Test01 : public Test
{
public:
    Test01(Scene* menu, string titleString);
    virtual ~Test01()
    {
    }

    virtual void update();
private:
    bool show_demo_window;
    bool show_another_window;
    vec4 clear_color;
};
