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
        // 渲染场景
        if (currentScene)
        {
            currentScene->render();
        }
        // 交换缓冲区
        glfwSwapBuffers(window);
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

    glfwTerminate();
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
	// 可能的全屏切换，没写事件监听就先将就一下吧
    // 回车不分大小键盘，alt只监听左边的
	if ((glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS|| glfwGetKey(window, GLFW_KEY_KP_ENTER) == GLFW_PRESS)
        && glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
	{
		if (!fullscreenSwitched)
		{
			config.isFullScreen = !config.isFullScreen;

			glfwSetWindowMonitor(window,
				config.isFullScreen ? glfwGetPrimaryMonitor() : NULL,
				0, 0, config.width, config.height, 0);
			// 如果是窗口化的化需要移动一下窗口，否则标题栏会看不见
			if (config.isFullScreen == false)
				glfwSetWindowPos(window, 100, 100);
			fullscreenSwitched = true;
		}
	}
	else {
		fullscreenSwitched = false;
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

int Game::getFPS()
{
	return FPS;
}