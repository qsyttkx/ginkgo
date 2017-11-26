#pragma once

#include <ginkgo.h>

using namespace ginkgo;

GameConfig readConfiguration(const char* filepath);

class TestScene :public Scene
{
public:
	Node* pointer;
	Node* root;
	Texture pointerImg, stageImg;
    Texture shiranui_idle[16];
	TestScene();
	virtual ~TestScene();
	virtual void update(float dt);
	float t;
    static std::string msg;
    void generateShiranui(glm::vec3 position, unsigned int offset = 0);
};

class TestGame :public Game
{
public:
	TestGame(GameConfig c = GameConfig());
};