#pragma once

#include <component.h>
#include <resource.h>
#include <vector>
#include <functional>

struct Animation
{
    // 每一帧持续的时间(毫秒)
    float delay;
    // 存放的帧列表
    std::vector<Texture> frames;
    // 循环次数，-1为死循环
    int loop;
};

class Animator:public Component
{
public:
    Animator();
    virtual ~Animator();
    virtual void update();
    // 播放一个动画
    void play(Animation *animation);
    bool isPlaying();
    void pause();
    void resume();
    void stop();
    // 当播放完毕时会调用的回调函数
    std::function<void()> stopCallback;
    // 当前播放到的帧
    int currentFrameIndex;
    // 当前播放的动画
    Animation *currentAnimation;
private:
    // 动画开始播放时的时刻
    float startTime;
    bool _isPlaying;
    // 播放上一动画帧的时刻
    float lastFrameTime;
    // 当前动画循环的次数
    int loop;
    // 精灵原本的纹理
    Texture* oriTexture;
};
