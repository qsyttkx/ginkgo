#pragma once

#include <ginkgo.h>

using namespace ginkgo;

GameConfig readConfiguration(const char* filepath);

class TestScene :public Scene
{
public:
	Sprite2D* logo;
	Sprite2D* welcome;
	Node* node1;
	TestScene();
	virtual void update(float dt);
};

class TestGame :public Game
{
public:
	TestGame(GameConfig c = GameConfig());
};