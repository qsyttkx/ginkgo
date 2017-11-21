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
    //TestScene2* scene = new TestScene2();
    this->replaceScene(scene);
}

// ����1
TestScene::TestScene() :Scene()
{
    name = "scene";
    root = new Node(this);
    root->position = vec3(Game::getConfigurations().width*0.5f, Game::getConfigurations().height*0.5f, 0);
    backgroundColor = vec3(1.0f);
    TextConfig c(24, vec4(0.2f, 0.2f, 0.2f, 1), "res/�������μ���.ttf",0.0f,2.0f,4.0f);
    welcome = new Text(root, Text::s2ws(msg), c);
    welcome->name = "welcome";
    welcome->position = vec3(-welcome->getSize().x*0.5f, welcome->getSize().y*0.5f - Game::getConfigurations().height*0.25f, 1.0f);
    // node
    node1 = new Node(root);
    node1->name = "node1";
    node1->position = vec3(0.0f, Game::getConfigurations().height*0.16f, 0.0f);
    node1->shouldSort = true;
    //node1->scaling.x = 2.0f;
    // sprite
    logoImg = Texture("res/logo.png");
    logo = new Sprite2D(node1, logoImg);
    logo->name = "logo";
    logo->scaling = vec3(0.8f);

    // pointer
    // �������
    glfwSetInputMode(Game::getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    pointer = new Node(this);
    pointer->position = vec3(0, 0, 1000);//��Ϊ1000Ϊ��֤��������Ϸ�
    pointerImg = Texture("res/pointer.png");
    auto pointerSprite = new Sprite2D(pointer, pointerImg);
    pointerSprite->position = vec3(13.0f, -12.0f, 0.0f);
    t = 0;
}

TestScene::~TestScene()
{
    logoImg.release();
    pointerImg.release();
}

void TestScene::update(float dt)
{
    node1->position = vec3(0.0f, Game::getConfigurations().height*0.16f + 50.0f * sin(t*3.14f), 0.0f);
    logo->rotation.z = -t*3.14f*0.3f;
    //root->rotation.z = -t*3.14f*0.1f;
    t += dt;

    GLFWwindow* window = Game::getWindow();

    static int statusR = GLFW_RELEASE;
    // ��r�л������������ش���
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE && statusR == GLFW_PRESS)
    {
        TestScene2* scene2 = new TestScene2();
        Game::replaceScene(scene2);
    }
    statusR = glfwGetKey(window, GLFW_KEY_R);
    // ��esc�˳�
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    // �������λ��
    double x, y;
    glfwGetCursorPos(Game::getWindow(), &x, &y);
    auto config = Game::getConfigurations();
    float px = float(x), py = (float)config.height - float(y);
    pointer->position.x = 0 > px ? 0 : (config.width < px ? config.width : px);
    pointer->position.y = 0 > py ? 0 : (config.height < py ? config.height : py);

    // �ڱ��������FPS
    stringstream ss;
    string fps;
    ss << Game::getFPS();
    ss >> fps;
    glfwSetWindowTitle(Game::getWindow(), (Game::getConfigurations().title + " [FPS: " + fps + "]").c_str());
}


// ����2

TestScene2::TestScene2() :Scene()
{
    name = "scene2";
    // ������ԭ���ƶ�����Ļ����
    position = vec3(Game::getConfigurations().width*0.5f, Game::getConfigurations().height*0.5f, 0);
    //backgroundColor = vec3(18, 121, 217) / 255.0f;
    backgroundColor = vec3(0.1f);
    logoImg = Texture("res/style-2.png");
    logo = new Sprite2D(this, logoImg);
    logo->name = "logo white";
    logo->position.y = Game::getConfigurations().height*0.16f;

    TextConfig c(24, vec4(1, 1, 1, 1), "res/�������μ���.ttf");
    text = new Text(this, L"Ginkgo: Hello TrueType Font!", c);
    text->name = "text";
    text->position = vec3(-text->getSize().x*0.5f, text->getSize().y*0.5f - Game::getConfigurations().height*0.16f, 1.0f);
    t = 0;
    timer1 = 0;

    glfwSetInputMode(Game::getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

TestScene2::~TestScene2()
{
    logoImg.release();
}

void TestScene2::update(float dt)
{
    logo->scaling = vec3(1.0f)*(0.8f + 0.2f*max(0.0f, sin(t*3.14f * 3.0f)));
    t += dt;

    GLFWwindow* window = Game::getWindow();
    
    // ˢ��Text
    wstring content = L"Ginkgo: Hello TrueType Font!";
    static unsigned int count = 0;
    float space = 2.0f / 3.0f;
    timer1 += dt;

    if (timer1 > space)
    {
        count += 1;
        if (count > content.length())
        {
            count = 0;
        }
        wstring wstr = content.substr(0, count);
        text->setText(wstr);
        timer1 -= space;
    }
    
    static int statusR = GLFW_RELEASE;
    // ��r�л������������ش���
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE && statusR == GLFW_PRESS)
    {
        TestScene* scene = new TestScene();
        Game::replaceScene(scene);
    }
    statusR = glfwGetKey(window, GLFW_KEY_R);
    // ��esc�˳�
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    // �ڱ��������FPS
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
    // ���ļ�
    if (fopen_s(&fp, path, "r"))
    {
        cout << "Shader[" << path << "]��ȡ����" << endl;
        return config;
    }
    // ��ȡ����
    char buff[512];
    while (fgets(buff, 512, fp))
    {
        code.append(buff);
    }
    fclose(fp);
    // ����
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
        hwnd = FindWindow(L"ConsoleWindowClass", NULL);//���������ڵ������ʹ�������ƥ��ָ�����ַ���,�������Ӵ��ڡ�  
        if (hwnd)
        {
            ShowWindow(hwnd, SW_HIDE);//����ָ�����ڵ���ʾ״̬  
        }
    }

    return config;
}