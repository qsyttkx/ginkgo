#pragma once
#include <macros.h>
#include <map>
#include <list>
#include <texture.h>
#include <functional>

namespace ginkgo
{
    struct Animation;

    // 动画控制器，讲道理应该是每个sprite有一个动画控制器
    class DLL Animator {
    public:
        // 构造函数
        Animator();
        // 激活、停止动画
        void setActive(bool isActive);
        // 更新动画状态
        void update(float dt);
        // 替换当前动画
        void replaceAnimation(Animation anim);
    protected:
        std::string currentAnimation;
        std::map<std::string, Animation> animations;
        bool isActive;
    };

    // 通用动画片段，意思就是不派生的话啥也做不了
    struct DLL Animation {
        Animation(std::string name);
        std::string name;
        virtual void update(float dt) {}
        bool loop;
        bool restoreTextureAtEnd;
        std::list<std::function<void(float, Animator)>> calls;
    };
    
    // 逐帧动画片段
    class DLL AnimationFrameByFrame :public Animation
    {
    public:
        AnimationFrameByFrame(std::string name);
        // 逐帧动画的帧
        class Frame
        {
            Texture img;
            float delay;
        };
        std::list<Frame> frames;
    };
}