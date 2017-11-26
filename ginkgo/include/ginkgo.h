#pragma once

/*包含第三方库的头文件*/
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/*包含ginkgo的头文件*/
#include <macros.h>
#include <scene.h>
#include <gameconfig.h>
#include <sprite.h>
#include <text.h>
#include <animation.h>

namespace ginkgo
{
    /// <summary>游戏主体</summary>
    /// <para>负责初始化各种接口、管理ginkgo的运行、场景切换、事件驱动等。调用run方法就可以启动游戏。</para>
	class DLL Game {
	public:
        /// <summary>构造一个游戏</summary>
        /// <param name="config">游戏配置，若空则为默认配置</param>
		Game(GameConfig config = GameConfig());
        /// <summary>析构函数，释放所有资源</summary>
		~Game();
        /// <summary>进入游戏的主循环中</summary>
        /// <returns>正常情况返回0</returns>
		int run();
        /// <summary>获取游戏配置。为静态方法（因为本框架只支持存在一个Game类在运行，所以就干脆直接把这些都设置为静态方法了）</summary>
        /// <returns>返回值为游戏配置</returns>
		static GameConfig getConfigurations();
        /// <summary>获取GLFWwindow*，以便于对窗口进行相关操作或者监听事件等。为静态方法</summary>
        /// <returns>返回值GLFWwindow*</returns>
		static GLFWwindow* getWindow();
        /// <summary>切换场景</summary>
        /// <param name="s">待切换的场景</param>
        /// <param name="releaseLastScene">是否释放上一个场景</param>
		static void replaceScene(Scene* s, bool releaseLastScene = true);
        /// <summary>获取当前游戏场景</summary>
        /// <returns>返回值Scene*为当前运行的游戏场景</returns>
		static Scene* getCurrentScene();
        /// <summary>获取当前的帧率</summary>
        /// <returns>返回值int为当前的FPS</returns>
		static int getFPS();
	private:
        /// <summary>游戏配置</summary>
		static GameConfig config;
        /// <summary>游戏配置。把GLFWwindow设为全局变量方便调用。但是这样一来我们的程序就只支持单个窗口了
        /// （实际上即便不设置成全局变量按我其他地方毫不区分当前上下文的写法运行多窗口也是会崩溃的=_=!）</summary>
		static GLFWwindow* window;
        /// <summary>当前活动的场景</summary>
		static Scene* currentScene;
        /// <summary>将被替换上来的场景</summary>
		static Scene* nextScene;
        /// <summary>用在替换场景时是否释放掉被替换的场景</summary>
		static bool releaseLastScene;
        /// <summary>全屏切换，由于此时还没做事件管理所以先弄个临时变量用一下</summary>
		bool fullscreenSwitched;
        /// <summary>切换全屏状态</summary>
		void switchFullscreen();
        /// <summary>计算FPS</summary>
		void countFPS();
        /// <summary>帧率</summary>
		static int FPS;
        /// <summary>上一帧时间，用来计算两帧之间的时间间隔。</summary>
        float lastTime;
	};

}
