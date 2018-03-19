#pragma once
#include <ginkgo.h>
#include <iostream>
#include "test.h"

using namespace glm;
using namespace std;

class SceneWelcome;

class Test04 : public Test
{
public:
    Test04(Scene* menu, string titleString);
    virtual ~Test04();
    virtual void update();
private:
    PhysicsWorld* phy;
    Sprite *bottomEdge, *leftEdge, *rightEdge, *topEdge;
    void setupABall(vec2 pos, vec2 v);
    void setupABlock(vec2 pos, vec2 v);
    vec2 mousePos;
    vec2 lastMousePos;
};
