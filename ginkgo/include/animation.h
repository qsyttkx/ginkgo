#pragma once
#include <macros.h>
#include <map>
#include <list>
#include <texture.h>
#include <functional>

namespace ginkgo
{
    struct Animation;

    // ������������������Ӧ����ÿ��sprite��һ������������
    class DLL Animator {
    public:
        // ���캯��
        Animator();
        // ���ֹͣ����
        void setActive(bool isActive);
        // ���¶���״̬
        void update(float dt);
        // �滻��ǰ����
        void replaceAnimation(Animation anim);
    protected:
        std::string currentAnimation;
        std::map<std::string, Animation> animations;
        bool isActive;
    };

    // ͨ�ö���Ƭ�Σ���˼���ǲ������Ļ�ɶҲ������
    struct DLL Animation {
        Animation(std::string name);
        std::string name;
        virtual void update(float dt) {}
        bool loop;
        bool restoreTextureAtEnd;
        std::list<std::function<void(float, Animator)>> calls;
    };
    
    // ��֡����Ƭ��
    class DLL AnimationFrameByFrame :public Animation
    {
    public:
        AnimationFrameByFrame(std::string name);
        // ��֡������֡
        class Frame
        {
            Texture img;
            float delay;
        };
        std::list<Frame> frames;
    };
}