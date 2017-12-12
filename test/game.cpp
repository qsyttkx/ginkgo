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
    name = "scene";
    GameConfig gc = Game::getConfigurations();

    backgroundColor = vec3(0.1f);

    logoImg = Texture("res/yaya.png");

    Shader* gray = new Shader("res/gray.vs", "res/gray.fs");
    gray->use();
    gray->setMat4("projection", mainCamera->projectionMatrix);
    gray->setMat4("view", mainCamera->getViewMatrix());

    // logo
    Sprite* logo1 = new Sprite(this, logoImg);
    logo1->position.x = -100.0f;
    logo1->position.y = gc.height * 0.125f;
    Sprite* logo2 = new Sprite(this, logoImg);
    logo2->position.x = 100.0f;
    logo2->position.y = gc.height * 0.125f;
    logo2->shader = gray;

    // 标题
    TextConfig config;
    config.color = vec4(1.0f);
    config.font = "res/Ginkgo775.ttf";
    config.size = 48;
    auto title = new Text(ui, L"HELLO!", config);
    title->position.y = gc.height * 0.25f - title->getSize().y*0.5f;
    title->position.x = (gc.width - title->getSize().x)*0.5f;
    title->position.z = 1.0f;

}

TestScene::~TestScene()
{
    logoImg.release();
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
