#pragma once

#include <string>
#include <macros.h>

// ��Ϸ����
struct DLL GameConfig
{
	std::string title;
	unsigned int width;
	unsigned int height;
	bool isFullScreen;
	bool isVSyncEnabled;
	GameConfig()
	{
		title = "Ginkgo";
		width = 640;
		height = 480;
		isFullScreen = false;
		isVSyncEnabled = true;
	}
};