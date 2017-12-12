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
    enum KeyState;

    //游戏主体
    //负责初始化各种接口、管理ginkgo的运行、场景切换、事件驱动等。调用run方法就可以启动游戏。
    class DLL Game {
    public:
        //构造一个游戏
        //游戏配置，若空则为默认配置
        Game(GameConfig config = GameConfig());
        //析构函数，释放所有资源
        ~Game();
        //进入游戏的主循环中
        //正常情况返回0
        int run();
        //获取游戏配置。为静态方法（因为只支持存在一个Game类在运行，所以就干脆直接把这些都设置为静态方法了）
        //返回值为游戏配置
        static GameConfig getConfigurations();
        //获取GLFWwindow*，以便于对窗口进行相关操作或者监听事件等。为静态方法
        //返回值GLFWwindow*
        static GLFWwindow* getWindow();
        //切换场景
        //待切换的场景
        //是否释放上一个场景
        static void replaceScene(Scene* s, bool releaseLastScene = true);
        //获取当前游戏场景
        //返回值Scene*为当前运行的游戏场景
        static Scene* getCurrentScene();
        //获取当前的帧率
        //返回值int为当前的FPS
        static int getFPS();
        // 获取按键状态，key的值使用GLFW库的键值（GLFW_KEY_）
        static KeyState getKey(int key);
    private:
        //游戏配置
        static GameConfig config;
        //游戏配置。把GLFWwindow设为全局变量方便调用。但是这样一来我们的程序就只支持单个窗口了
        //实际上即便不设置成全局变量按我其他地方毫不区分当前上下文的写法运行多窗口也是会崩溃的=_=!）
        static GLFWwindow* window;
        //当前活动的场景
        static Scene* currentScene;
        //将被替换上来的场景
        static Scene* nextScene;
        //用在替换场景时是否释放掉被替换的场景
        static bool releaseLastScene;
        //切换全屏状态
        void switchFullscreen();
        //计算FPS
        void countFPS();
        //帧率
        static int FPS;
        //上一帧时间，用来计算两帧之间的时间间隔。
        float lastTime;

        // 键盘事件监测
        static void keyeventCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
        //release 0,press 1
        static KeyState keyStates[350];
        // 在每轮渲染中遍历键值状态，将瞬间状态修改为持续状态
        void checkKeyState();
    };

    enum KeyState
    {
        // 抬起的状态
        release,
        // 按下的状态
        press,
        // 抬起的瞬间
        posedge,
        // 按下的瞬间
        negedge
    };
}
