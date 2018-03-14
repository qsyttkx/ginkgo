#include <animation.h>
#include <ginkgo.h>

Animator::Animator()
{
    startTime = Game::getInstance()->getTime();
    lastFrameTime = startTime;
    _isPlaying = false;
    currentFrameIndex = 0;
    loop = 0;
    stopCallback = [](){};
    oriTexture = nullptr;
}

Animator::~Animator()
{
    if(oriTexture)delete(oriTexture);
}

void Animator::update()
{
    if(!isPlaying())return;// 如果不是处于播放的状态就不管它

    // host是我们要控制的精灵
    Sprite* sp = static_cast<Sprite*>(host);
    float delay = currentAnimation->delay;// 获取每帧的持续时间
    float time = Game::getInstance()->getTime();// 获取现在的时刻
    float dt = time - lastFrameTime; //此刻距离上一动画帧的时刻
    // 判断是否切换动画帧
    while(dt-delay>0)
    {
        sp->setTexture(currentAnimation->frames[currentFrameIndex]);
        dt-=delay;
        ++currentFrameIndex;
        lastFrameTime = time;
        // 当动画播放到头时
        if(currentFrameIndex==currentAnimation->frames.size())
        {
            // 死循环则回到第一帧
            if(currentAnimation->loop <= -1)
            {
                currentFrameIndex = 0;
            }
            // 还没到循环次数则回到第一帧
            else if(currentAnimation->loop > loop)
            {
                ++loop;
                currentFrameIndex = 0;
            }
            // 停止动画
            else
            {
                stop();
            }
        }
    }
}

void Animator::play(Animation *animation)
{
    startTime = Game::getInstance()->getTime();
    lastFrameTime = startTime;
    currentAnimation = animation;
    currentFrameIndex = 0;
    loop = 0;
    _isPlaying = true;
    if(oriTexture==nullptr)
    {
        oriTexture = new Texture(((Sprite*)host)->getTexture());
    }
}

bool Animator::isPlaying()
{
    return _isPlaying;
}


void Animator::pause()
{
    _isPlaying = false;
}

void Animator::resume()
{
    _isPlaying = true;
}

void Animator::stop()
{
    _isPlaying = false;
    currentFrameIndex = 0;
    ((Sprite*)host)->setTexture(*oriTexture);
    stopCallback();
}
