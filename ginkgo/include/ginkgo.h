#pragma once

/*包含第三方库的头文件*/
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

/*包含ginkgo的头文件*/
#include <macros.h>
#include <scene.h>
#include <gameconfig.h>
#include <sprite2d.h>

namespace ginkgo
{
	// 游戏主体
	class DLL Game {
	public:
		Game(GameConfig config = GameConfig());
		~Game();
		int run();
		static GameConfig getConfigurations();
		static GLFWwindow* getWindow();
		// 切换场景(Scene待切换的场景，bool是否释放上一个场景)
		static void replaceScene(Scene* s, bool releaseLastScene = true);
		static Scene* getCurrentScene();
		void init(GameConfig config);
		static int getFPS();
	private:
		static GameConfig config;
		// 把GLFWwindow设为全局变量，方便调用，但是这样一来我们的程序就只支持
		// 单个窗口了（实际上即便不设置成全局变量按我其他地方毫不区分当前窗口的
		// 写法运行多窗口也是会崩溃的=_=!）
		static GLFWwindow* window;
		static Scene* currentScene;
		static Scene* nextScene;
		static bool releaseLastScene;

		// 全屏切换，由于还没做事件管理所以先弄个临时变量用一下
		bool fullscreenSwitched;
		void switchFullscreen();

		// FPS
		void countFPS();
		static int FPS;
	};

}
