#pragma once
#include <macros.h>
#include <map>
#include <list>
#include <texture.h>
#include <functional>
#include <sprite.h>

namespace ginkgo
{
    class Animation;

    // 动画控制器，讲道理应该每个sprite有一个动画控制器
    class DLL Animator : public Node
    {
    public:
        // 构造函数
        Animator(Sprite* parent);
        // 更新动画状态
        virtual void update(float dt);
        // 渲染子节点
        virtual void renderChildren();
        // 替换当前动画
        void replaceAnimation(Animation* anim);
        // 替换当前动画
        void replaceAnimation(std::string animName);
        // 激活、停止动画
        void setActive(bool isActive);
    private:
        // 动画激活状态
        bool isActive;
    };

    // 动画中的回调函数，float为本动画播放到当前持续的时间，Animation*为当前播放的动画
    typedef std::function<void(float, Animation*)> AnimationCallback;

    class DLL Animation : public Node
    {
    public:
        Animation(Animator* parent, std::string name = "");
        void setEnabled(bool enalbed);
        virtual void update(float dt);
        // 渲染子节点
        virtual void renderChildren();
        float TimeAtBegin;
        float TimeOfAnimation;
        float timeOfFrame;
        float fps;
        unsigned int frameCount;
        // 动画在游戏每次更新画面时的回调函数。float为本动画播放到当前持续的时间，Animation*为当前播放的动画
        AnimationCallback onUpdated;
        // 动画本身每一帧更新时的回调函数。float为本动画播放到当前持续的时间，Animation*为当前播放的动画
        AnimationCallback onFrameChanged;
        // 动画在结束时的回调函数。float为本动画播放到当前持续的时间，Animation*为当前播放的动画
        AnimationCallback onAnimationEnded;
        void pushbackFrameFromTexture(Texture texture);
    };
}