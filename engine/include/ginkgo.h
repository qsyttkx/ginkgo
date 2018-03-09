/*引擎的主头文件*/
#pragma once

// 默认的配置文件路径
#define DEFAULT_CONFIG_FILE_PATH "res/config.json"
// 默认窗口标题
#define DEFAULT_WINDOW_TITLE "Ginkgo"

// 包含第三方库的头文件
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <node.h>
#include <scene.h>
#include <resource.h>
#include <sprite.h>
#include <button.h>
#include <label.h>
#include <physics.h>

struct Configuration
{
    unsigned int height;
    unsigned int width;
    bool fullscreen;
    bool vsync;
};

class Game
{
public:
    Game();
    virtual ~Game();
    // 运行游戏
    int run();
    // 结束游戏
    void end();
    // 改变窗口标题
    void setTitle(std::string title);
    // 改变窗口大小
    void setWindowSize(unsigned int width, unsigned int height);
    // 获取窗口大小
    glm::vec2 getWindowSize();
    // 获取鼠标位置
    glm::vec2 getMousePosition();
    // 获取glfw窗口
    GLFWwindow* getGLFWwindow();
    // 切换场景
    void replaceScene(Scene* s, bool releaseLastScene = true);
    // 获取运行时间
    float getTime();
    // 获取距上一帧之间的时间间隔
    float getDeltaTime();
    // 获取全局唯一的游戏实体
    static Game* getInstance();
    // 键盘事件监听器列表
    std::list<KeyboardEventListener*> keyboardEventListeners;
    // 鼠标时间监听器列表
    std::list<MouseEventListener*> mouseEventListeners;
private:
    static Game* _instance;

    GLFWwindow* window;

    Configuration config;
    // 读取配置文件
    void readConfiguration();
    // 创建配置文件
    void createConfiguration();

    // 渲染画面
    void render();
    // 处理事件
    void pollEvents();

    // 场景
    Scene* currentScene;
    Scene* nextScene;
    bool releaseLastScene;

    // 时间管理
    float time, lastTime, deltaTime;

    // 资源管理
    ResourceManager* resManager;

    // 键盘事件回调
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    // 鼠标按钮事件回调
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    // 鼠标移动事件回调
    static void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);
    // 鼠标滚动事件回调
    static void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};