#pragma once
#include <ginkgo.h>
#include <iostream>

using namespace glm;
using namespace std;

class SceneWelcome;

class Test02 : public Scene
{
public:
    Test02(Scene* menu);

    virtual ~Test02()
    {
        shader1.release();
        ResourceManager::getInstance()->releaseTexture("btn1_normal");
        ResourceManager::getInstance()->releaseTexture("btn1_pressed");
    }

    virtual void update();
private:
    // 菜单场景
    Scene* menuScene;
    // 返回按钮
    Button *btn_back;
    // 标题标签
    Label *title;

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
