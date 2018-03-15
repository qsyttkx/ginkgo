#pragma once
#include <ginkgo.h>
#include <iostream>
#include "test.h"

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

class Test03 : public Test
{
public:

    Test03(Scene* menu, string titleString);

    virtual ~Test03();
    virtual void update();
private:
    Node* root;
    K *k;
};
