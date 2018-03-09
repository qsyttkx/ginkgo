#pragma once

#include <Box2D/Box2D.h>
#include <component.h>
#include <glm/glm.hpp>

class Physics :public Component
{
public:
    Physics();
    Physics(glm::vec2 gravity);
    virtual ~Physics();
    virtual void update();
    void setStepInterval(float interval);
    b2World* getWorld();
    bool running;
private:
    b2World* world;
    float interval;// 迭代间隔时间
    int32 velocityIterations;
    int32 positionIterations;
    float fixtime;// 防止box2D迭代出现问题
};