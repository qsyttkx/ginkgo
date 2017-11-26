#define EXPORT
#include <macros.h>
#include <animation.h>

using namespace ginkgo;

ginkgo::Animator::Animator(Sprite * parent):Node(parent)
{
    isActive = false;
}

void ginkgo::Animator::update(float dt)
{
    if (!isActive)return;

    Node::update(dt);
}

void ginkgo::Animator::renderChildren()
{
    if (!isActive)return;

    Node::renderChildren();
}

void ginkgo::Animator::replaceAnimation(Animation* anim)
{
    auto children = getChildren();
    for (auto i = children.begin(); i != children.end(); i++)
    {
        ((Animation*)*i)->setEnabled((*i) == anim);
    }
}

void ginkgo::Animator::replaceAnimation(std::string animName)
{
    auto children = getChildren();
    for (auto i = children.begin(); i != children.end(); i++)
    {
        ((Animation*)*i)->setEnabled((*i)->name == animName);
    }
}

void Animator::setActive(bool isActive)
{
    if (parent)((Sprite*)parent)->isPlayingAnimation = isActive;
    this->isActive = isActive;
}

ginkgo::Animation::Animation(Animator* parent, std::string name) :Node(parent)
{
    this->name = name;
    TimeAtBegin = (float)glfwGetTime();
    timeOfFrame = TimeOfAnimation = 0.0f;
    frameCount = 0;
}

void ginkgo::Animation::setEnabled(bool enalbed)
{
    isEnabled = enalbed;
    if (isEnabled)
    {
        timeOfFrame = TimeOfAnimation = 0.0f;
        frameCount = 0;
    }
}

void ginkgo::Animation::update(float dt)
{
    Node::update(dt);

    TimeOfAnimation += dt;
    timeOfFrame += dt;

    float delay = 1.0f / fps;
    if (timeOfFrame >= delay)
    {
        timeOfFrame -= delay;
        ++frameCount;
        if (frameCount >= getChildren().size())
        {
            frameCount = 0;
            //TimeOfAnimation = 0;
        }
    }
}

void ginkgo::Animation::renderChildren()
{
    std::list<Node*> children = getChildren();
    // 没有帧被载入的话就不渲染了
    if (children.size() == 0)return;

    // 定位当前帧
    auto iter = children.begin();
    for (unsigned int i = 1; i < frameCount; i++)
        iter++;
    if (iter == children.end())return;

    (*iter)->renderHeader();
    (*iter)->update(dt);
    (*iter)->renderChildren();
}

void ginkgo::Animation::pushbackFrameFromTexture(Texture texture)
{
    Sprite* sp = new Sprite(this, texture);
}
