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

    GameConfig gc = Game::getConfigurations();
    mainCamera->position = vec3(-160.0f, 50.0f, 800.0f);
    mainCamera->rotation = vec3(-15.0f, -70.0f, 0.0f);

    root = new Node(this);
    //root->position = vec3(Game::getConfigurations().width*0.5f, Game::getConfigurations().height*0.5f, 0);
    backgroundColor = vec3(1.0f);

    // 舞台背景
    stageImg = Texture("res/stage/stage_static.png");
    Sprite* stage = new Sprite(root, stageImg);
    //stage->opacity = 0.3f;

    // 标题
    TextConfig config;
    config.color = vec4(1.0f, 0.2f, 0.0f, 0.8f);
    config.font = "res/Ginkgo775.ttf";
    auto title = new Text(ui, Text::s2ws(msg), config);
    //title->position.y = Game::getConfigurations().height - 40.0f;
    //title->position.x = 40.0f;
    title->position.z = 1.0f;

    // 火舞
    // 载入纹理资源
    char buff[64];
    for (int i = 0; i < 16; i++)
    {
        sprintf_s(buff, "res/shiranui/shiranui%02d.png", i);
        shiranui_idle[i] = Texture(buff);
    }
    // 生成精灵
    Sprite* shiranui1 = new Sprite(root,shiranui_idle[0]);
    shiranui1->position = vec3(-150.0f, -150, 200);
    shiranui1->scaling = vec3(1.5f);
    //shiranui->scaling.x = -1.0f;//反转一下
    // 载入动画
    Animator* animator1 = new Animator(shiranui1);
    Animation* idle1 = new Animation(animator1, "idle");
    idle1->onAnimationEnded = [](float time, Animation*)
    {
        cout << "CallBack! Time: " << time << endl;
    };
    idle1->callbacks.push_back([=](float time, Animation* anim)
    {
        if (time > 5)
        {
            static_cast<Animator*>(anim->getParent())->setActive(false);
            title->setText(L"Stopped!");
        }
    });
    for (int i = 0; i < 16; i++)
    {
        idle1->pushbackFrameFromTexture(shiranui_idle[i]);
    }
    idle1->fps = 15.0f;
    animator1->replaceAnimation("idle");
    animator1->setActive(true);
}

TestScene::~TestScene()
{
    stageImg.release();
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

    // 在标题上添加FPS
    stringstream ss;
    string fps;
    ss << Game::getFPS();
    ss >> fps;
    glfwSetWindowTitle(Game::getWindow(), (Game::getConfigurations().title + " [FPS: " + fps + "]").c_str());
}

void TestScene::generateShiranui(vec3 position, unsigned int offset)
{
    
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
