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
    // ��ʼ��glfw, ʹ��OpenGL 3.x�汾��core profile
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);//��ֹ�������ڴ�С

    GLFWmonitor* monitor = config.isFullScreen ? glfwGetPrimaryMonitor() : NULL;
    window = glfwCreateWindow(config.width, config.height, config.title.c_str(), monitor, NULL);
    if (window == NULL)
    {
        cout << "����GLFW����ʧ��" << endl;
        glfwTerminate();
        return;
    }
    // �Դ˴���Ϊ��ǰ������
    glfwMakeContextCurrent(window);
    // ��ʼ��glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "��ʼ��GLADʧ��" << endl;
        return;
    }

    // �������ÿ�����ֱͬ��
    if (config.isVSyncEnabled)
    {
        glfwSwapInterval(1);
    }

	// �����ڽ�����ɫ��
	Shader::buildBuiltinShaders();

    currentScene = NULL;
    nextScene = NULL;

    cout << "��ʼ�����!" << endl;
}

Game::~Game()
{
    if (currentScene)
    {
        delete(currentScene);
    }
    glfwTerminate();
    cout << config.title << " ��ֹͣ" << endl;
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
    cout << config.title << " ��������" << endl;
    // ��Ⱦѭ��
    while (!glfwWindowShouldClose(window))
    {
        // ��Ⱦ����
        if (currentScene)
        {
            currentScene->render();
        }
        // ����������
        glfwSwapBuffers(window);
		// glfw�����¼�
		glfwPollEvents();
		
		// ����Ѿ�����һ�������������һ�������л�����
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
	// ���ܵ�ȫ���л���ûд�¼��������Ƚ���һ�°�
    // �س����ִ�С���̣�altֻ������ߵ�
	if ((glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS|| glfwGetKey(window, GLFW_KEY_KP_ENTER) == GLFW_PRESS)
        && glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
	{
		if (!fullscreenSwitched)
		{
			config.isFullScreen = !config.isFullScreen;

			glfwSetWindowMonitor(window,
				config.isFullScreen ? glfwGetPrimaryMonitor() : NULL,
				0, 0, config.width, config.height, 0);
			// ����Ǵ��ڻ��Ļ���Ҫ�ƶ�һ�´��ڣ�����������ῴ����
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