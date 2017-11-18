#include <ginkgo.h>
#include <stb_image.h>
#include <iostream>
#include <shader.h>

using namespace std;
using namespace ginkgo;

GLFWwindow* Game::window = NULL;
GameConfig Game::config;
Scene* Game::currentScene = NULL;

Game::Game(GameConfig config)
{
    init(config);
}

void Game::init(GameConfig config)
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

    currentScene = NULL;

    // 初始化内建着色器
    Shader::buildBuiltinShaders();

    cout << "初始化完毕!" << endl;
    return;
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
		
		// 可能的全屏切换
		if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
		{
			if (!fullscreenSwitched)
			{
				config.isFullScreen = !config.isFullScreen;
				
				glfwSetWindowMonitor(window,
					config.isFullScreen ? glfwGetPrimaryMonitor() : NULL,
					0, 0, config.width,config.height, 0);
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

    glfwTerminate();
    return 0;
}

void Game::setCurrentScene(Scene* s)
{
    currentScene = s;
}

Scene* Game::getCurrentScene()
{
    return currentScene;
}