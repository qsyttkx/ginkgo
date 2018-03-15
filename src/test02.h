#pragma once
#include <ginkgo.h>
#include <iostream>
#include "test.h"

using namespace glm;
using namespace std;

class SceneWelcome;

class Test02 : public Test
{
public:
    Test02(Scene* menu, string titleString);

    virtual ~Test02()
    {
        shader1.release();
    }

    virtual void update();
private:
    Camera* camera1;
    Shader shader1;
    Label* labels[6];
    // 放置一些标签
    void setLabels();
    Node* labelsRoot;
    // 放置一些按钮
    void setButtons();
    Node* buttonsRoot;
};
