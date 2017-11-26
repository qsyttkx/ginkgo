#include "game.h"
#include <rapidjson/document.h>
#include <sstream>

using namespace rapidjson;
using namespace std;
using namespace glm;

string TestScene::msg;
TestGame::TestGame(GameConfig c) :Game(c)
{
    TestScene* scene = new TestScene();
    this->replaceScene(scene);
}

// 场景1
TestScene::TestScene() :Scene()
{
    name = "scene";
    root = new Node(this);
    root->position = vec3(Game::getConfigurations().width*0.5f, Game::getConfigurations().height*0.5f, 0);
    backgroundColor = vec3(1.0f);

    // 舞台背景
    stageImg = Texture("res/stage/stage_static.png");
    Sprite* stage = new Sprite(root, stageImg);

    // 标题
    TextConfig config;
    config.color = vec4(1.0f, 0.2f, 0.0f, 0.8f);
    config.font = "res/Ginkgo775.ttf";
    auto title = new Text(this, Text::s2ws(msg),config);
    title->position.y = Game::getConfigurations().height - 40.0f;
    title->position.x = 40.0f;

    // 火舞
    // 载入纹理资源
    char buff[64];
    for (int i = 0; i < 16; i++)
    {
        sprintf_s(buff, "res/shiranui/shiranui%02d.png", i);
        shiranui_idle[i] = Texture(buff);
    }
    // 生成精灵
    for (int i = 0; i < 4; i++)
        generateShiranui(vec3((i - 1.5f)*120.0f, -100, 0), (3 - i) * 2);
    for (int i = 0; i < 4; i++)
        generateShiranui(vec3((i - 1.5f)*150.0f, -150, 0), (3 - i) * 2);

    // pointer
    // 隐藏鼠标
    glfwSetInputMode(Game::getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    pointer = new Node(this);
    pointer->position = vec3(0, 0, 1000);//设为1000为保证鼠标在最上方
    pointerImg = Texture("res/pointer.png");
    auto pointerSprite = new Sprite(pointer, pointerImg);
    pointerSprite->position = vec3(13.0f, -12.0f, 0.0f);
    t = 0;
}

TestScene::~TestScene()
{
    stageImg.release();
    pointerImg.release();
    for (int i = 0; i < 16; i++)
    {
        shiranui_idle[i].release();
    }
}

void TestScene::update(float dt)
{
    Scene::update(dt);

    GLFWwindow* window = Game::getWindow();

    // 按esc退出
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    // 设置鼠标位置
    double x, y;
    glfwGetCursorPos(Game::getWindow(), &x, &y);
    auto config = Game::getConfigurations();
    float px = float(x), py = (float)config.height - float(y);
    pointer->position.x = 0 > px ? 0 : (config.width < px ? config.width : px);
    pointer->position.y = 0 > py ? 0 : (config.height < py ? config.height : py);

    // 在标题上添加FPS
    stringstream ss;
    string fps;
    ss << Game::getFPS();
    ss >> fps;
    glfwSetWindowTitle(Game::getWindow(), (Game::getConfigurations().title + " [FPS: " + fps + "]").c_str());
}

void TestScene::generateShiranui(vec3 position, unsigned int offset)
{
    Sprite* shiranui1 = new Sprite(root);
    shiranui1->position = position;
    //shiranui->scaling.x = -1.0f;//反转一下
    // 载入动画
    Animator* animator1 = new Animator(shiranui1);
    Animation* idle1 = new Animation(animator1, "idle");
    char buff[64];
    for (int i = 0; i < 16; i++)
    {
        sprintf_s(buff, "res/shiranui/shiranui%02d.png", i);
        shiranui_idle[i] = Texture(buff);
        idle1->pushbackFrameFromTexture(shiranui_idle[i]);
    }
    idle1->fps = 15.0f;
    animator1->replaceAnimation("idle");
    idle1->frameCount = offset;//稍微不同步一下
    animator1->setActive(true);
}

GameConfig readConfiguration(const char* path)
{
    GameConfig config;
    FILE* fp;
    std::string code = "";
    // 打开文件
    if (fopen_s(&fp, path, "r"))
    {
        cout << "Shader[" << path << "]读取错误" << endl;
        return config;
    }
    // 读取内容
    char buff[512];
    while (fgets(buff, 512, fp))
    {
        code.append(buff);
    }
    fclose(fp);
    // 解析
    Document d;
    d.Parse(code.c_str());
    config.title = d["title"].GetString();
    config.width = d["width"].GetUint();
    config.height = d["height"].GetUint();
    config.isFullScreen = d["isFullScreen"].GetBool();
    config.isVSyncEnabled = d["isVSyncEnabled"].GetBool();
    TestScene::msg = d["msg"].GetString();
    if (d["hideConsole"].GetBool())
    {
        HWND hwnd;
        hwnd = FindWindow(L"ConsoleWindowClass", NULL);//处理顶级窗口的类名和窗口名称匹配指定的字符串,不搜索子窗口。  
        if (hwnd)
        {
            ShowWindow(hwnd, SW_HIDE);//设置指定窗口的显示状态  
        }
    }

    return config;
}