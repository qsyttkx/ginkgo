#include "test02.h"
#include "welcome.h"
#include <glm/gtc/matrix_transform.hpp>
#include <sstream>

Test02::Test02(Scene* menu)
{
    name = "Test02";
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
    title = new Label("02. Graphical User Interface (builtin)", FontStyle(32));
    addChild(title);
    title->setPosition((wSize.x - title->getContainSize().x) / 2, wSize.y - 50.0f, 1.0f);

    auto manager = ResourceManager::getInstance();
    manager->loadTexture("btn1_normal", "res/btn1_normal.png");
    manager->loadTexture("btn1_pressed", "res/btn1_pressed.png");

    // 我们新建一个相机，产生一个透视的效果
    camera1 = new Camera();
    addChild(camera1);
    camera1->setPosition(0,0, 600.0f);
    camera1->projectionMatrix = glm::perspective(glm::radians(60.0f),wSize.x/(wSize.y+1.0f),0.1f,3000.0f);
    // 新建另一个着色器来使用这个相机
    shader1 = Shader("basicDiffuse");

    setLabels();
    setButtons();
}

void Test02::update()
{
    Scene::update();

    camera1->updateCameraVectors();
    camera1->setProjectionAndView(&shader1);

    float t = Game::getInstance()->getTime();
    for(int i = 0;i<6;++i)
    {
        labels[i]->setPosition(0, 60.0f * sin(3.14159f*i/3.0f+t),60.0f*cos(3.14159f*i/3.0f+t));
    }
    float mousex = Game::getInstance()->getMousePosition().x / Game::getInstance()->getWindowSize().x;
    float mousey = Game::getInstance()->getMousePosition().y / Game::getInstance()->getWindowSize().y;
    labelsRoot->setRotation(glm::radians(30.0f*(mousey-0.5f)),glm::radians(45.0f*(mousex-0.5f)),0);
    buttonsRoot->setRotation(glm::radians(30.0f*(mousey-0.5f)),glm::radians(45.0f*(mousex-0.5f)),0);
}

void Test02::setLabels()
{
    glm::vec2 wSize = Game::getInstance()->getWindowSize();

    auto hint = new Label("There are some labels:");
    addChild(hint);
    hint->setPosition(300,550);

    labelsRoot = new Node();
    addChild(labelsRoot);
    labelsRoot->setShader(&shader1);
    labelsRoot->setPosition(-300.0f,0);
    // labelsRoot->setRotation(0,-glm::radians(15.0f),0);

    FontStyle style(32);
    string texts[] = {"Hello, world!", "你好，世界", "Welcome to Ginkgo", "&*H(JFfg2324...", "3.1415926","abcdefghijklmn"};
    for(int i = 0;i<6;++i)
    {
        style.color.r = style.color.r+1.0f/6.0f;
        style.color.g = style.color.g+0.3f/6.0f;
        labels[i] = new Label(texts[i],style);
        labelsRoot->addChild(labels[i]);
    }
}

void Test02::setButtons()
{
    glm::vec2 wSize = Game::getInstance()->getWindowSize();
    Label* hint = new Label("There are some buttons:");
    addChild(hint);
    hint->setPosition(850,550);

    buttonsRoot = new Node();
    addChild(buttonsRoot);
    buttonsRoot->setShader(&shader1);
    buttonsRoot->setPosition(300,0);
    auto btn1 = new Button(this, "btn1_normal","btn1_pressed");
    btn1->setText("按钮1");
    buttonsRoot->addChild(btn1);
    btn1->onClick = [=](int key, int mods)
    {
        std::stringstream ss;
        ss<<"btn 1 clicked! key: "<<key<<", mods: "<<mods;
        cout<<ss.str()<<endl;
        hint->setText(ss.str());
    };
    btn1->setPosition(0,100,-30);

    auto btn2 = new Button(this, "btn1_normal","btn1_pressed");
    btn2->setText("按钮2");
    buttonsRoot->addChild(btn2);
    btn2->onClick = [=](int key, int mods)
    {
        std::stringstream ss;
        ss<<"btn 2 clicked! key: "<<key<<", mods: "<<mods;
        cout<<ss.str()<<endl;
        hint->setText(ss.str());
    };
    btn2->setPosition(0,0,0);
    btn2->setRotation(glm::radians(30.0f));

    auto btn3 = new Button(this, "btn1_normal","btn1_pressed");
    btn3->setText("按钮3");
    buttonsRoot->addChild(btn3);
    btn3->onClick = [=](int key, int mods)
    {
        std::stringstream ss;
        ss<<"btn 3 clicked! key: "<<key<<", mods: "<<mods;
        cout<<ss.str()<<endl;
        hint->setText(ss.str());
    };
    btn3->setPosition(0,-100,30);
    btn3->setRotation(glm::radians(-45.0f));
}
