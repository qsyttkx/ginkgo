#pragma once

#include <ginkgo.h>

using namespace ginkgo;

GameConfig readConfiguration(const char* filepath);

class TestScene :public Scene
{
public:
	Sprite2D* logo;
	Text* welcome;
	Node* pointer;
	Node* node1;
    Node* root;
	Texture logoImg, pointerImg;
	TestScene();
	virtual ~TestScene();
	virtual void update(float dt);
	float t;
    static std::string msg;
};

class TestScene2 :public Scene
{
public:
	Sprite2D* logo;
    Text* text;
	Texture logoImg;
	TestScene2();
	virtual ~TestScene2();
	virtual void update(float dt);
	float t;
    float timer1;
};

class TestGame :public Game
{
public:
	TestGame(GameConfig c = GameConfig());
};