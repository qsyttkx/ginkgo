#include <ginkgo.h>
#include <shader.h>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
using namespace rapidjson;

Game *Game::_instance = nullptr;

Game::Game()
{
    if (_instance != nullptr)
        return;
    //游戏启动时先读取配置文件
    readConfiguration();
    // 初始化glfw, 使用OpenGL 3.x版本，core profile
    glfwSetErrorCallback(error_callback);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); //禁止调整窗口大小
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
    glfwWindowHint(GLFW_SAMPLES, 4);// 多重采样数
    GLFWmonitor *monitor = config.fullscreen ? glfwGetPrimaryMonitor() : NULL;
    window = glfwCreateWindow(config.width, config.height, DEFAULT_WINDOW_TITLE, monitor, NULL);
    if (window == NULL)
    {
        cerr << "Failed to create GLFW window!" << endl;
        glfwTerminate();
        return;
    }
    // 以此窗口为当前上下文
    glfwMakeContextCurrent(window);
    // 初始化glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cerr << "Failed to initialize glad!" << endl;
        glfwTerminate();
        return;
    }
    // 根据配置开启垂直同步
    if (config.vsync)
    {
#ifdef _WIN32
    // Turn on vertical screen sync under Windows.
    // (I.e. it uses the WGL_EXT_swap_control extension)
    typedef BOOL (WINAPI *PFNWGLSWAPINTERVALEXTPROC)(int interval);
    PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;
    wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
    if(wglSwapIntervalEXT)
        wglSwapIntervalEXT(config.vsync);
#else
        glfwSwapInterval(config.vsync);
#endif
    }
    // 启用多重采样
    glEnable(GL_MULTISAMPLE);
    // 编译内建着色器
    Shader::buildBuiltinShaders();
    // 初始化纹理管理器
    resManager = new ResourceManager();
    // 初始化精灵的顶点坐标数据
    Sprite::generateVertices();
    currentScene = nullptr;
    nextScene = nullptr;
    time = lastTime = deltaTime = 0.0f;
    // 赋此实例为全局对象
    _instance = this;
    // 初始化ImGUI
    // Setup ImGui binding
    ImGui_ImplGlfwGL3_Init(window, false);
    // Setup style
    ImGui::StyleColorsClassic();
    //ImGui::StyleColorsDark();

    // 设置键盘事件回调
    glfwSetKeyCallback(window,key_callback);
    // 设置鼠标事件回调
    glfwSetMouseButtonCallback(window,mouse_button_callback);
    glfwSetCursorPosCallback(window,mouse_move_callback);
    glfwSetScrollCallback(window,mouse_scroll_callback);
    // 设置SetCharCallback
    glfwSetCharCallback(window, ImGui_ImplGlfwGL3_CharCallback);

    cout << "Initialization complete." << endl;
}

Game::~Game()
{
    if (currentScene)
    {
        delete (currentScene);
    }

    delete (resManager);
    Sprite::deleteVertices();

    ImGui_ImplGlfwGL3_Shutdown();

    glfwTerminate();
    _instance = nullptr;
}

int Game::run()
{
    while (!glfwWindowShouldClose(window))
    {
        // 渲染
        render();
        // 处理事件
        pollEvents();
    }

    return 0;
}

void Game::end()
{
    glfwSetWindowShouldClose(window, GL_TRUE);
}

void Game::setTitle(string title)
{
    glfwSetWindowTitle(window, title.c_str());
}

void Game::setWindowSize(unsigned int width, unsigned int height)
{
    glfwSetWindowSize(window, width, height);
}

glm::vec2 Game::getWindowSize()
{
    return glm::vec2(config.width, config.height);
}

void Game::replaceScene(Scene *s, bool releaseLastScene)
{
    this->releaseLastScene = releaseLastScene;
    nextScene = s;
}

glm::vec2 Game::getMousePosition()
{
    double xp, yp;
    glfwGetCursorPos(window, &xp, &yp);
    return glm::vec2((float)xp, (float)yp);
}

GLFWwindow *Game::getGLFWwindow()
{
    return window;
}

void Game::render()
{
    // 渲染场景
    if (currentScene)
    {
        currentScene->traverse();
    }

    // 交换缓冲
    glfwSwapBuffers(window);
}

void Game::pollEvents()
{
    glfwPollEvents();

    // 更新时间
    lastTime = time;
    time = (float)glfwGetTime();
    deltaTime = time - lastTime;

    // 如果已经有下一个场景，则把下一个场景切换过来
    if (nextScene)
    {
        if (releaseLastScene && currentScene)
            delete (currentScene);
        currentScene = nextScene;
        nextScene = NULL;
        cout << "Scene [" << currentScene->name << "] is on stage." << endl;
    }

    // 检查音效
    Music::checkSounds();
}

void Game::readConfiguration()
{
    ifstream file(DEFAULT_CONFIG_FILE_PATH);
    Document doc;

    if (!file.is_open())
    {
        file.close();
        cerr << "Can't read configuration file!" << endl;
        createConfiguration();
        return;
    }

    cout << "Reading configuraion file..." << endl;
    string dump = string(istreambuf_iterator<char>(file), istreambuf_iterator<char>());
    doc.Parse(dump.c_str());
    if (doc.HasParseError())
    {
        cerr << "Configuration file parsed error!" << endl;
        createConfiguration();
        return;
    }
    // 读取各项属性
    config.width = doc.HasMember("width") && doc["width"].IsInt() ? doc["width"].GetInt() : 1280;
    config.height = doc.HasMember("height") && doc["height"].IsInt() ? doc["height"].GetInt() : 720;
    config.fullscreen = doc.HasMember("fullscreen") && doc["fullscreen"].IsBool() ? doc["fullscreen"].GetBool() : false;
    config.vsync = doc.HasMember("vsync") && doc["vsync"].IsInt() ? doc["vsync"].GetInt() : 1;
}

void Game::createConfiguration()
{
    Document doc;
    // 对于未读取到或者读取出现错误的情况，创建新的配置文件
    config.width = 1280;
    config.height = 720;
    config.fullscreen = false;
    config.vsync = 1;
    doc.SetObject();
    doc.AddMember("width", (int)config.width, doc.GetAllocator());
    doc.AddMember("height", (int)config.height, doc.GetAllocator());
    doc.AddMember("fullscreen", config.fullscreen, doc.GetAllocator());
    doc.AddMember("vsync", config.vsync, doc.GetAllocator());
    cout << "Create new configuration file..." << endl;
    ofstream newfile(DEFAULT_CONFIG_FILE_PATH, ios::out);
    if (!newfile.is_open())
    {
        cerr << "Can't create new file!" << endl;
        return;
    }
    StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);
    doc.Accept(writer);
    newfile << sb.GetString();
    newfile.close();
}

float Game::getTime()
{
    return time;
}

float Game::getDeltaTime()
{
    return deltaTime;
}

Game *Game::getInstance()
{
    return _instance;
}

void Game::error_callback(int error, const char* description)
{
    cerr<<"Error "<<error<<", : "<<description<<endl;
}

void Game::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // ImGui
    ImGui_ImplGlfwGL3_KeyCallback(window,key,scancode,action,mods);

    // 切换全屏
    if((key == GLFW_KEY_ENTER || key == GLFW_KEY_KP_ENTER) && action == GLFW_PRESS && mods == GLFW_MOD_ALT)
    {
        Configuration conf = Game::getInstance()->config;
        conf.fullscreen = !conf.fullscreen;
        Game::getInstance()->config = conf;

        glfwSetWindowMonitor(window,
            conf.fullscreen ? glfwGetPrimaryMonitor() : NULL,
            0, 0, conf.width, conf.height, 0);
        // 如果是窗口化的化需要移动一下窗口，否则标题栏会看不见
        if (conf.fullscreen == false)
            glfwSetWindowPos(window, 100, 100);
    }

    // cout<<"key :"<<key<<"action"<<action<<endl;
    if(Game::getInstance()->currentScene)
    {
        auto &listeners = Game::getInstance()->currentScene->keyboardEventListeners;
        for(auto iter = listeners.begin();iter!=listeners.end();++iter)
        {
            if((*iter)->callback(key, scancode, action,mods))break;
        }
    }

}


void Game::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    // ImGui
    ImGui_ImplGlfwGL3_MouseButtonCallback(window,button,action,mods);

    // cout<<"button :"<<button<<"action"<<action<<endl;
    if(Game::getInstance()->currentScene)
    {
        auto &listeners = Game::getInstance()->currentScene->mouseEventListeners;
        for(auto iter = listeners.begin();iter!=listeners.end();++iter)
        {
            if((*iter)->buttonCallback(button, action,mods))break;
        }
    }
}

void Game::mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
{
    // cout<<"button :"<<button<<"action"<<action<<endl;
    if(Game::getInstance()->currentScene)
    {
        auto &listeners = Game::getInstance()->currentScene->mouseEventListeners;
        for(auto iter = listeners.begin();iter!=listeners.end();++iter)
        {
            if((*iter)->moveCallback(glm::vec2(float(xpos), float(ypos))))break;
        }
    }
}

void Game::mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    // ImGui
    ImGui_ImplGlfwGL3_ScrollCallback(window,xoffset,yoffset);

    // cout<<"button :"<<button<<"action"<<action<<endl;
    if(Game::getInstance()->currentScene)
    {
        auto &listeners = Game::getInstance()->currentScene->mouseEventListeners;
        for(auto iter = listeners.begin();iter!=listeners.end();++iter)
        {
            if((*iter)->scrollCallback(glm::vec2(float(xoffset), float(yoffset))))break;
        }
    }
}
