#pragma once

#include <ginkgo.h>

using namespace ginkgo;

GameConfig readConfiguration(const char* filepath);

class TestScene :public Scene
{
public:
	Sprite2D* logo;
	Sprite2D* welcome;
	Sprite2D* pointer;
	Node* node1;
	TestScene();
	virtual void update(float dt);
	float t;
};

class TestScene2 :public Scene
{
public:
	Sprite2D* logo;
	TestScene2();
	virtual void update(float dt);
	float t;
};

class TestGame :public Game
{
public:
	TestGame(GameConfig c = GameConfig());
};