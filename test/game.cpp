#include "game.h"
#include <rapidjson/document.h>

using namespace rapidjson;
using namespace std;

TestScene::TestScene() :Scene()
{
	name = "scene";
	backgroundColor = glm::vec3(1.0f);
	Texture welcomeImg("res/welcome.png");
	welcome = new Sprite2D(welcomeImg, this);
	welcome->name = "welcome";
	welcome->position = glm::vec3(0.0f, -100.0f, 2.0f);
	welcome->scaling = glm::vec3(0.5f);
	// node
	node1 = new Node(this);
	node1->name = "node1";
	node1->position = glm::vec3(0.0f, 100.0f, 1.0f);
	// sprite
	Texture logoImg("res/logo.png");
	logo = new Sprite2D(logoImg, node1);
	logo->name = "logo";
	logo->scaling = glm::vec3(0.5f);
}
void TestScene::update(float dt)
{
	Scene::update(dt);
	static float t = 0;
	node1->position = glm::vec3(0.0f, 100.0f + 10.0f * glm::sin(t*3.14f), 1.0f);
	logo->rotation.z = -t*3.14f*0.1f;
	t += dt;

	GLFWwindow* window = Game::getWindow();
}
TestGame::TestGame(GameConfig c) :Game(c)
{
	TestScene* scene = new TestScene();
	this->setCurrentScene(scene);
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