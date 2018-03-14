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
    // 播放一个动画
    void play(Animation animation);
private:
    // 当前播放到的帧
    int currentFrameIndex;
    // 动画开始播放时的时间
    float startTime;
};
