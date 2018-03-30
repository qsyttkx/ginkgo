#pragma once
#include <ginkgo.h>
#include <iostream>
#include "test.h"

using namespace glm;
using namespace std;

class SceneWelcome;

class TapSprite :public Sprite
{
public:
    TapSprite(vec2 pos);
    virtual ~TapSprite();
    virtual void update();
private:
    float bornTime;
};

class Test05 : public Test
{
public:
    Test05(Scene* menu, string titleString);
    virtual ~Test05();
    virtual void update();
private:
    bool isPlaying;
    float volume;
    MouseEventListener *listener;
};
