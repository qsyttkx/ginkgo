#pragma once
#include <ginkgo.h>
#include <iostream>

using namespace glm;
using namespace std;

class SceneWelcome;

class K :public Sprite
{
public:
    K();
    virtual ~K();
    virtual void update();
    Animator animator;
    Animation idle;
    Animation walk;
    Animation run;
    bool direction;// 1为右，0为左
    float lastKeyATime;
    float lastKeyDTime;
};

class Test03 : public Scene
{
public:

    Test03(Scene* menu);

    virtual ~Test03();
private:
    // 菜单场景
    Scene* menuScene;
    // 返回按钮
    Button *btn_back;
    // 标题标签
    Label *title;
    virtual void update();
    void loadResource();
    Node* root;
    K *k;
};
