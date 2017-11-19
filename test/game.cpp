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

// ����1
TestScene::TestScene() :Scene()
{
	name = "scene";
	Node* root = new Node(this);
	root->position = vec3(Game::getConfigurations().width*0.5f, Game::getConfigurations().height*0.5f, 0);
	backgroundColor = vec3(1.0f);
	Texture welcomeImg("res/welcome.png");
	welcome = new Sprite2D(welcomeImg, root);
	welcome->name = "welcome";
	welcome->position = vec3(0.0f, 0.0f, -1.0f);
	welcome->shouldSort = true;
	// node
	node1 = new Node(root);
	node1->name = "node1";
	node1->position = vec3(0.0f, 0.0f, 0.0f);
	node1->shouldSort = true;
	// sprite
	Texture logoImg("res/logo.png");
	logo = new Sprite2D(logoImg, node1);
	logo->name = "logo";
	logo->scaling = vec3(1.5f);

	// pointer
	// �������
	glfwSetInputMode(Game::getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	Texture pointerImg("res/pointer.png");
	pointer = new Sprite2D(pointerImg, this);
	pointer->position = vec3(0, 0, 1000);//��Ϊ1000Ϊ��֤��������Ϸ�
	t = 0;
}

void TestScene::update(float dt)
{
	Scene::update(dt);
	node1->position = vec3(0.0f, 10.0f * sin(t*3.14f), 0.0f);
	logo->rotation.z = -t*3.14f*0.1f;
	t += dt;

	GLFWwindow* window = Game::getWindow();

	static bool statusR = GLFW_RELEASE;
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
	pointer->position.x = float(x);
	pointer->position.y = (float)Game::getConfigurations().height - float(y);

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
	backgroundColor = vec3(18, 121, 217) / 255.0f;
	Texture logoImg("res/style-2.png");
	logo = new Sprite2D(logoImg, this);
	logo->name = "logo white";
	t = 0;

	glfwSetInputMode(Game::getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void TestScene2::update(float dt)
{
	Scene::update(dt);
	logo->scaling = vec3(1.0f)*(0.8f + 0.2f*max(0.0f, sin(t*3.14f * 3.0f)));
	t += dt;

	GLFWwindow* window = Game::getWindow();

	static bool statusR = GLFW_RELEASE;
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