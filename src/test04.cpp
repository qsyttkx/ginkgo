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
}

Test04::~Test04()
{
}

void Test04::update()
{
    Test::update();
}
