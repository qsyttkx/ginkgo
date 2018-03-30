#include "test04.h"

Test04::Test04(Scene* menu, string titleString):Test(menu,titleString)
{
    phy = new PhysicsWorld();
    addComponent("physics_world", phy);

    // 放置边界
    vec2 wSize = Game::getInstance()->getWindowSize();
    bottomEdge = new Sprite("edge");
    addChild(bottomEdge);
    bottomEdge->setScale(wSize.x/10.0f, 1.0f);
    bottomEdge->setPosition(wSize.x*0.5f,10.0f);
    topEdge = new Sprite("edge");
    addChild(topEdge);
    topEdge->setScale(wSize.x/10.0f, 1.0f);
    topEdge->setPosition(wSize.x*0.5f,wSize.y - 10.0f);
    leftEdge = new Sprite("edge");
    addChild(leftEdge);
    leftEdge->setScale(1.0f, wSize.y/10.0f);
    leftEdge->setPosition(10.0f, wSize.y*0.5f);
    rightEdge = new Sprite("edge");
    addChild(rightEdge);
    rightEdge->setScale(1.0f, wSize.y/10.0f);
    rightEdge->setPosition(wSize.x - 10.0f, wSize.y*0.5f);
    // 设置边界的物理参数
    b2BodyDef edgeBodyDef1;
    edgeBodyDef1.position.Set(wSize.x*0.5f*DEFAULT_MEASURING_SCALE,10.0f*DEFAULT_MEASURING_SCALE);
    b2Body* edgeBody1 = phy->getWorld()->CreateBody(&edgeBodyDef1);
    b2PolygonShape edgeShape1;
    edgeShape1.SetAsBox(wSize.x*0.5f*DEFAULT_MEASURING_SCALE,10.0f*DEFAULT_MEASURING_SCALE);
    edgeBody1->CreateFixture(&edgeShape1,0.0f);

    edgeBodyDef1.position.Set(wSize.x*0.5f*DEFAULT_MEASURING_SCALE,(wSize.y-10.0f)*DEFAULT_MEASURING_SCALE);
    b2Body* edgeBody2 = phy->getWorld()->CreateBody(&edgeBodyDef1);
    edgeBody2->CreateFixture(&edgeShape1,0.0f);

    b2BodyDef edgeBodyDef2;
    edgeBodyDef2.position.Set(10.0f*DEFAULT_MEASURING_SCALE,wSize.y*0.5f*DEFAULT_MEASURING_SCALE);
    b2Body* edgeBody3 = phy->getWorld()->CreateBody(&edgeBodyDef2);
    b2PolygonShape edgeShape2;
    edgeShape2.SetAsBox(10.0f*DEFAULT_MEASURING_SCALE,wSize.y*0.5f*DEFAULT_MEASURING_SCALE);
    edgeBody3->CreateFixture(&edgeShape2,0.0f);

    edgeBodyDef2.position.Set((wSize.x - 10.0f)*DEFAULT_MEASURING_SCALE,wSize.y*0.5f*DEFAULT_MEASURING_SCALE);
    b2Body* edgeBody4 = phy->getWorld()->CreateBody(&edgeBodyDef2);
    edgeBody4->CreateFixture(&edgeShape2,0.0f);

    setupABall(wSize*0.5f,vec2(0,300));
    setupABall(wSize*0.5f,vec2(50,500));
    setupABall(wSize*0.5f,vec2(-50,500));

    // 放置标签
    Label* hint = new Label("左键在任意处放置一个小球，右键在任意处放置一个方块");
    addChild(hint);
    hint->setPosition(50,wSize.y*0.8f,1);

    MouseEventListener* mlistener = new MouseEventListener(this);
    mlistener->buttonCallback = [=](int button, int action, int mods)
    {
        if(action==GLFW_PRESS)
        {
            lastMousePos = Game::getInstance()->getMousePosition();
            lastMousePos.y = wSize.y - lastMousePos.y;
        }

        if(action==GLFW_RELEASE && button == 0)
        {
            mousePos = Game::getInstance()->getMousePosition();
            mousePos.y = wSize.y - mousePos.y;
            setupABall(mousePos,(mousePos-lastMousePos)*2.0f);
        }
        else if(action==GLFW_RELEASE && button == 1)
        {
            mousePos = Game::getInstance()->getMousePosition();
            mousePos.y = wSize.y - mousePos.y;
            setupABlock(mousePos,(mousePos-lastMousePos)*2.0f);
        }
        return false;
    };
}

Test04::~Test04()
{
}

void Test04::update()
{
    Test::update();
}

void Test04::setupABall(vec2 pos, vec2 v)
{
    float s = float(rand()%10)/10.0f+0.5f;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.x*DEFAULT_MEASURING_SCALE,pos.y*DEFAULT_MEASURING_SCALE);
    bodyDef.linearVelocity.Set(v.x*DEFAULT_MEASURING_SCALE,v.y*DEFAULT_MEASURING_SCALE);
    b2Body* body = phy->getWorld()->CreateBody(&bodyDef);
    b2CircleShape circle;
    circle.m_radius = s*25.0f * DEFAULT_MEASURING_SCALE;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.8f;
    body->CreateFixture(&fixtureDef);

    Sprite* ball = new Sprite("ball");
    ball->setPosition(pos);
    ball->setScale(s);
    addChild(ball);
    BodySynchronizer* synchronizer = new BodySynchronizer(body);
    ball->addComponent("sync", synchronizer);
}

void Test04::setupABlock(vec2 pos, vec2 v)
{
    float s = float(rand()%10)/10.0f+0.5f;
    float a = float(rand()%360)/360.0f*2.0f*3.14159f;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pos.x*DEFAULT_MEASURING_SCALE,pos.y*DEFAULT_MEASURING_SCALE);
    bodyDef.angle = a;
    bodyDef.linearVelocity.Set(v.x*DEFAULT_MEASURING_SCALE,v.y*DEFAULT_MEASURING_SCALE);
    b2Body* body = phy->getWorld()->CreateBody(&bodyDef);
    b2PolygonShape box;
    box.SetAsBox(s*25.0f * DEFAULT_MEASURING_SCALE,s*25.0f * DEFAULT_MEASURING_SCALE);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &box;
    fixtureDef.density = 10.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.1f;
    body->CreateFixture(&fixtureDef);

    Sprite* block = new Sprite("block");
    block->setPosition(pos);
    block->setScale(s);
    addChild(block);
    BodySynchronizer* synchronizer = new BodySynchronizer(body);
    block->addComponent("sync", synchronizer);
}
