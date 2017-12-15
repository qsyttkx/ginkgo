#include "game.h"
#include <rapidjson/document.h>
#include <sstream>

using namespace rapidjson;
using namespace std;
using namespace glm;

TestGame::TestGame(GameConfig c) :Game(c)
{
    TestScene* scene = new TestScene();
    this->replaceScene(scene);
}

// 场景1
TestScene::TestScene() :Scene()
{
    float width = (float)Game::getConfigurations().width;
    float height = (float)Game::getConfigurations().height;
    
    TTFCharacter::loadFont("C:/Windows/Fonts/Dengb.ttf");
    s = new Shader("res/effect.vs", "res/effect.fs");
    root->shader = s;

    Layer* layer1 = new Layer(this);
    layer1->position.z = 10;

    logoImg = Texture("res/logo.png");
    Sprite* logo = new Sprite(root, logoImg);
    logo->position = vec3(width *0.5f-100, height*0.5f, 1.0f);
    Sprite* bg = new Sprite(root, Texture("res/bg.png"));
    bg->position = vec3(width *0.5f, height*0.5f, 0.0f);

    TextConfig c;
    c.font = "C:/Windows/Fonts/Dengb.ttf";
    c.color = vec4(0.3f, 0.8f, 1.0f, 1);
    c.size = 48;
    Sprite* logo2 = new Sprite(layer1, logoImg);
    logo2->position = vec3(width*0.5f, height*0.5f, 0.0f);
    Text* txt = new Text(layer1, L"Framebuffer and shader test", c);
    txt->position = vec3((width-txt->getSize().x)*0.5f, 100, 0);
}

TestScene::~TestScene()
{
    logoImg.release();
}

void TestScene::update(float dt)
{
    Scene::update(dt);

    static float t = 0;
    t += dt;

    s->use();
    s->setFloat("tm", t);
        
    GLFWwindow* window = Game::getWindow();

    // 按esc退出
    if (Game::getKey(GLFW_KEY_ESCAPE) == posedge)
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


GameConfig readConfiguration(const char* path)
{
    GameConfig config;
    FILE* fp;
    std::string code = "";
    // 打开文件
    if (fopen_s(&fp, path, "r"))
    {
        cout << "Configuration[" << path << "]读取错误" << endl;
        return config;
    }
    // 读取内容
    char buff[512];
    while (fgets(buff, 512, fp))
    {
        code.append(buff);
    }
    fclose(fp);
    // 解析，这个地方没有做解析失败的判断啊，如果config.json有问题会崩溃的
    Document d;
    d.Parse(code.c_str());
    config.title = d["title"].GetString();
    config.width = d["width"].GetUint();
    config.height = d["height"].GetUint();
    config.isFullScreen = d["isFullScreen"].GetBool();
    config.isVSyncEnabled = d["isVSyncEnabled"].GetBool();
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
