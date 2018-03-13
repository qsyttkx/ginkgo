#pragma once

#include <component.h>
#include <resource.h>
#include <list>

class Animation
{
public:
    Animation();
    virtual ~Animation();
    // 每一帧持续的时间(毫秒)
    float delay;
    // 存放的帧列表
    std::list<Texture> frames;
};

class Animator:public Component
{
public:
    Animator();
    virtual ~Animator();
    virtual void update();
};
