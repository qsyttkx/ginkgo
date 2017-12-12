#define EXPORT
#include <macros.h>
#include <ginkgo.h>
#include <stb_image.h>
#include <iostream>
#include <shader.h>

using namespace std;
using namespace ginkgo;

GLFWwindow* Game::window = NULL;
GameConfig Game::config;
Scene* Game::currentScene = NULL;
Scene* Game::nextScene = NULL;
bool Game::releaseLastScene = true;
int Game::FPS = 0;
KeyState Game::keyStates[350] = { KeyState::release };

Game::Game(GameConfig config)
{
    this->config = config;
    // 初始化glfw, 使用OpenGL 3.x版本，core profile
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);//禁止调整窗口大小

    GLFWmonitor* monitor = config.isFullScreen ? glfwGetPrimaryMonitor() : NULL;
    window = glfwCreateWindow(config.width, config.height, config.title.c_str(), monitor, NULL);
    if (window == NULL)
    {
        cout << "创建GLFW窗口失败" << endl;
        glfwTerminate();
        return;
    }
    // 以此窗口为当前上下文
    glfwMakeContextCurrent(window);

    // 监听键盘事件
    glfwSetKeyCallback(window, keyeventCallback);

    // 初始化glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "初始化GLAD失败" << endl;
        return;
    }

    // 根据配置开启垂直同步
    if (config.isVSyncEnabled)
    {
        glfwSwapInterval(1);
    }

    // 编译内建的着色器
    Shader::buildBuiltinShaders();

    currentScene = NULL;
    nextScene = NULL;

    cout << "初始化完毕!" << endl;
}

Game::~Game()
{
    if (currentScene)
    {
        delete(currentScene);
    }
    glfwTerminate();
    cout << config.title << " 已停止" << endl;
}

GameConfig Game::getConfigurations()
{
    return config;
}

GLFWwindow* Game::getWindow()
{
    return window;
}

int Game::run()
{
    cout << config.title << " 正在运行" << endl;
    // 渲染循环
    while (!glfwWindowShouldClose(window))
    {
        float time = (float)glfwGetTime();
        // 渲染场景
        if (currentScene)
        {
            currentScene->update(time - lastTime);
        }
        lastTime = time;
        // 交换缓冲区
        glfwSwapBuffers(window);
        // 检查键盘状态
        checkKeyState();
        // glfw处理事件
        glfwPollEvents();

        // 如果已经有下一个场景，则把下一个场景切换过来
        if (nextScene)
        {
            if (releaseLastScene && currentScene)delete(currentScene);
            currentScene = nextScene;
            nextScene = NULL;
            cout << "Scene[" << currentScene->name << "] is on stage." << endl;
        }
        switchFullscreen();

        countFPS();
    }

    return 0;
}

void Game::replaceScene(Scene* s, bool releaseLastScene)
{
    Game::releaseLastScene = releaseLastScene;
    nextScene = s;
}

Scene* Game::getCurrentScene()
{
    return currentScene;
}

void Game::switchFullscreen()
{
    // 回车不分大小键盘，alt只监听左边的
    bool enter = (getKey(GLFW_KEY_ENTER) == negedge || getKey(GLFW_KEY_KP_ENTER) == negedge);
    bool alt = (getKey(GLFW_KEY_LEFT_ALT) == press || getKey(GLFW_KEY_LEFT_ALT) == negedge);
    if (enter && alt)
    {
        config.isFullScreen = !config.isFullScreen;

        glfwSetWindowMonitor(window,
            config.isFullScreen ? glfwGetPrimaryMonitor() : NULL,
            0, 0, config.width, config.height, 0);
        // 如果是窗口化的化需要移动一下窗口，否则标题栏会看不见
        if (config.isFullScreen == false)
            glfwSetWindowPos(window, 100, 100);
    }
}

void Game::countFPS()
{
    static float t = 0;
    static float lasttime = 0;
    static int count = 0;

    count++;
    float time = (float)glfwGetTime();
    t += time - lasttime;
    lasttime = time;
    if (t > 1.0f)
    {
        t -= 1.0f;
        FPS = count;
        count = 0;
    }
}

void Game::keyeventCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    //printf("key: %d, scancode: %d, action: %d, mods: %d\n", key, scancode, action, mods);
    if (key == GLFW_KEY_UNKNOWN)return;

    if (action == GLFW_RELEASE)
    {
        keyStates[key] = posedge;
    }
    else if (action == GLFW_PRESS)
    {
        keyStates[key] = negedge;
    }//忽略GLFW_REPEAT了
}

int Game::getFPS()
{
    return FPS;
}

KeyState Game::getKey(int key)
{
    KeyState s = keyStates[key];
    return s;
}

void Game::checkKeyState()
{
    for (int i = 0; i < sizeof(keyStates) / sizeof(KeyState); ++i)
    {
        // 如果是边沿的那么这次是边沿的情况，接下来把它置为0或者1的形式
        if (keyStates[i] == posedge)keyStates[i] = release;
        else if (keyStates[i] == negedge)keyStates[i] = press;
    }
}