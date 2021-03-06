#include <physics.h>
#include <ginkgo.h>

using namespace glm;

PhysicsWorld::PhysicsWorld():PhysicsWorld(vec2(0.0f,-10.0f))
{
}

PhysicsWorld::PhysicsWorld(vec2 gravity)
{
    b2Vec2 g(gravity.x,gravity.y);
    world = new b2World(g);
    fixtime = 0.0f;
    interval = 1.0f/60.0f;// 默认设置迭代速度为60次每秒
    velocityIterations = 6;
    positionIterations = 2;
    running = true;
}


PhysicsWorld::~PhysicsWorld()
{
    delete(world);
}

void PhysicsWorld::update()
{
    if(!running)return;

    float dt = Game::getInstance()->getDeltaTime();
    // dt是两帧之间间隔的时间，很可能是一个波动的值
    // 而box2D迭代的时间间隔需要是一个定值才行，否则可能会出现bug
    fixtime+=dt;
    while (fixtime > interval) {
        world->Step(interval,velocityIterations,positionIterations);
        fixtime-=interval;
    }
}

void PhysicsWorld::setStepInterval(float interval)
{
    this->interval = interval;
}

b2World* PhysicsWorld::getWorld()
{
    return world;
}

BodySynchronizer::BodySynchronizer(b2Body *body)
{
    this->body = body;
}

BodySynchronizer::~BodySynchronizer()
{

}

void BodySynchronizer::update()
{
    b2Vec2 position = body->GetPosition();
    float angle = body->GetAngle();
    host->setPosition(position.x/DEFAULT_MEASURING_SCALE, position.y/DEFAULT_MEASURING_SCALE);
    host->setRotation(angle);
}
