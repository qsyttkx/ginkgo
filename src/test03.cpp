#include "test03.h"
#include "welcome.h"

Test03::Test03(Scene* menu, string titleString):Test(menu,titleString)
{
    name = "Test03";
    Sprite* wasd = new Sprite("wasd");
    addChild(wasd);
    wasd->setPosition(300,75);

    root = new Node();
    root->setScale(3.0f);
    addChild(root);

    k = new K();
    root->addChild(k);
    k->setPosition(100,40);
}

Test03::~Test03()
{
}

void Test03::update()
{
    Scene::update();

}

K::K()
{
    setAnchor(0.5f,0.0f);//设置原点为脚下
    setTexture("res/k/idle0039.png");

    char path[64];
    auto manager = ResourceManager::getInstance();
    idle.delay = 0.066f; // 15FPS
    for(int i = 0;i<40;i++)
    {
        sprintf(path,"res/k/idle%04d.png",i);
        idle.frames.push_back(manager->getTexture(path));
    }
    idle.loop = 0;

    walk.delay = 0.066f; // 15FPS
    for(int i = 0;i<12;i++)
    {
        sprintf(path,"res/k/walk%04d.png",i);
        walk.frames.push_back(manager->getTexture(path));
    }
    walk.loop = -1;

    run.delay = 0.066f; // 15FPS
    for(int i = 0;i<8;i++)
    {
        sprintf(path,"res/k/run%04d.png",i);
        run.frames.push_back(manager->getTexture(path));
    }
    run.loop = -1;

    animator = Animator();
    addComponent("animator",&animator);
    animator.play(&idle);
    direction = 1;

    float t = Game::getInstance()->getTime();
    lastKeyATime=t-1.0f;
    lastKeyDTime=t-1.0f;
}

K::~K()
{

}

void K::update()
{
    Sprite::update();
    vec2 wSize = Game::getInstance()->getWindowSize();
    setScale(float(direction)*2.0f-1.0f,1.0f);
    int keyA = glfwGetKey(Game::getInstance()->getGLFWwindow(),GLFW_KEY_A);
    int keyD = glfwGetKey(Game::getInstance()->getGLFWwindow(),GLFW_KEY_D);
    float t = Game::getInstance()->getTime();

    // 当正在idle且按下A时，播放向左走的动画
    if(animator.currentAnimation == &idle && keyA)
    {
        direction = 0;
        if(t-lastKeyATime < 1.0f)
        {
            animator.play(&run);
        }
        else
        {
            animator.play(&walk);
        }
    }
    // 当正在idle且按下D时，播放向右走的动画
    else if(animator.currentAnimation == &idle && keyD)
    {
        direction = 1;
        if(t-lastKeyDTime < 1.0f)
        {
            animator.play(&run);
        }
        else
        {
            animator.play(&walk);
        }
    }

    // 当正在走时
    if(animator.currentAnimation == &walk)
    {
        vec2 pos = getPosition();
        pos.x+=(direction*2.0f-1.0f)*60.0f*Game::getInstance()->getDeltaTime();
        if(pos.x<40.0f)pos.x=40.0f;
        else if(pos.x>(wSize.x - 80.0f)/3.0f)pos.x=(wSize.x - 80.0f)/3.0f;
        setPosition(pos);

        if(keyA && !keyD)
        {
            direction = 0;
        }
        else if(!keyA && keyD)
        {
            direction = 1;
        }
        else if(!keyA && !keyD)
        {
            animator.play(&idle);
        }
    }

    // 当在跑时
    if(animator.currentAnimation == &run)
    {
        vec2 pos = getPosition();
        pos.x+=(direction*2.0f-1.0f)*250.0f*Game::getInstance()->getDeltaTime();
        if(pos.x<40.0f)pos.x=40.0f;
        else if(pos.x>(wSize.x - 80.0f)/3.0f)pos.x=(wSize.x - 80.0f)/3.0f;
        setPosition(pos);

        if(keyA && !keyD)
        {
            direction = 0;
        }
        else if(!keyA && keyD)
        {
            direction = 1;
        }
        else if(!keyA && !keyD)
        {
            animator.play(&idle);
        }
    }

    if(keyA)lastKeyATime=t;
    if(keyD)lastKeyDTime=t;
}
