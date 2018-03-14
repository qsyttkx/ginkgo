#include "test03.h"
#include "welcome.h"

Test03::Test03(Scene* menu)
{
    name = "Test03";
    menuScene = menu;
    // 设置白色背景
    setBackgroundColor(vec4(1.0f, 1.0f, 1.0f, 1.0f));
    // 获取游戏窗口的尺寸(画面的尺寸，不包含标题栏和边框)
    glm::vec2 wSize = Game::getInstance()->getWindowSize();
    // 初始化按钮
    btn_back = new Button(this, "btn_normal", "btn_pressed", "btn_hover");
    addChild(btn_back);
    btn_back->setText("返回", FontStyle(18));
    btn_back->onClick = [=](int key, int mods) {
        // 设置回白色背景
        setBackgroundColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        // 返回菜单
        Game::getInstance()->replaceScene(menu);
    };
    // 为节点设置位置的z值可以影响渲染次序，z值越高的越先渲染
    btn_back->setPosition(wSize.x - 75.0f, 50.0f, 1);
    // 初始化标题标签
    title = new Label("03. Sprite Animation", FontStyle(32));
    addChild(title);
    title->setPosition((wSize.x - title->getContainSize().x) / 2, wSize.y - 50.0f, 1.0f);

    loadResource();

    Sprite* wasd = new Sprite("wasd");
    addChild(wasd);
    wasd->setPosition(300,50);

    root = new Node();
    root->setScale(3.0f);
    addChild(root);

    k = new K();
    root->addChild(k);
    k->setPosition(100,40);
}

Test03::~Test03()
{
    char path[64];
    auto manager = ResourceManager::getInstance();
    for(int i = 0;i<40;i++)
    {
        sprintf(path,"res/k/idle%04d.png",i);
        manager->releaseTexture(path);
    }
    for(int i = 0;i<12;i++)
    {
        sprintf(path,"res/k/walk%04d.png",i);
        manager->releaseTexture(path);
    }

    for(int i = 0;i<8;i++)
    {
        sprintf(path,"res/k/run%04d.png",i);
        manager->releaseTexture(path);
    }
    manager->releaseTexture("wasd");
}

void Test03::loadResource()
{
    char path[64];
    auto manager = ResourceManager::getInstance();
    for(int i = 0;i<40;i++)
    {
        sprintf(path,"res/k/idle%04d.png",i);
        manager->loadTexture(path,path);
    }

    for(int i = 0;i<12;i++)
    {
        sprintf(path,"res/k/walk%04d.png",i);
        manager->loadTexture(path,path);
    }

    for(int i = 0;i<8;i++)
    {
        sprintf(path,"res/k/run%04d.png",i);
        manager->loadTexture(path,path);
    }

    manager->loadTexture("wasd","res/wasd.png");
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
}

K::~K()
{

}

void K::update()
{
    Sprite::update();
    setScale(float(direction)*2.0f-1.0f,1.0f);
    int keyA = glfwGetKey(Game::getInstance()->getGLFWwindow(),GLFW_KEY_A);
    int keyD = glfwGetKey(Game::getInstance()->getGLFWwindow(),GLFW_KEY_D);
    float t = Game::getInstance()->getTime();
    if(lastKeyATime==0)lastKeyATime=t;
    if(lastKeyDTime==0)lastKeyDTime=t;

    cout<<keyA<<keyD<<endl;
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
        else if(pos.x>1200.0f/3.0f)pos.x=1200.0f/3.0f;
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
        pos.x+=(direction*2.0f-1.0f)*200.0f*Game::getInstance()->getDeltaTime();
        if(pos.x<40.0f)pos.x=40.0f;
        else if(pos.x>1200.0f/3.0f)pos.x=1200.0f/3.0f;
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
