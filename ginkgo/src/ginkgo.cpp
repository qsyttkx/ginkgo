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

    currentScene = NULL;

    // ��ʼ���ڽ���ɫ��
    Shader::buildBuiltinShaders();

    cout << "��ʼ�����!" << endl;
    return;
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
		
		// ���ܵ�ȫ���л�
		if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
		{
			if (!fullscreenSwitched)
			{
				config.isFullScreen = !config.isFullScreen;
				
				glfwSetWindowMonitor(window,
					config.isFullScreen ? glfwGetPrimaryMonitor() : NULL,
					0, 0, config.width,config.height, 0);
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