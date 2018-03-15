#pragma once
#include <ginkgo.h>
#include <iostream>
#include "test01.h"
#include "test02.h"
#include "test03.h"

using namespace glm;
using namespace std;

class SceneWelcome : public Scene
{
public:
    // 关闭按钮
    Button *btn_exit;
    // 标题标签
    Label *title;
    // 图标精灵
    Sprite *logo;

    SceneWelcome()
    {
        name = "SceneWelcome";
        // 设置白色背景
        setBackgroundColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        // 获取游戏窗口的尺寸(画面的尺寸，不包含标题栏和边框)
        glm::vec2 wSize = Game::getInstance()->getWindowSize();
        // 初始化按钮
        btn_exit = new Button(this, "btn_normal", "btn_pressed", "btn_hover");
        addChild(btn_exit);
        btn_exit->setText("退出", FontStyle(18));
        btn_exit->onClick = [=](int key, int mods) {
            // 释放资源，结束游戏
            Game::getInstance()->end();
        };
        // 为节点设置位置的z值可以影响渲染次序，z值越高的越先渲染
        btn_exit->setPosition(wSize.x - 75.0f, 50.0f, 1);
        // 初始化标题标签
        title = new Label("Ginkgo2 Test", FontStyle(48));
        addChild(title);
        title->setPosition((wSize.x - title->getContainSize().x) / 2, wSize.y - 50.0f, 1.0f);
        // 初始化图标精灵
        logo = new Sprite("logo");
        addChild(logo);
        logo->setPosition(wSize * 0.5f);
        // 对菜单UI进行初始化
        setupImGui();
    }

    virtual ~SceneWelcome()
    {
        // 释放资源
        auto manager = ResourceManager::getInstance();
        manager->releaseAllFontsTTF();
        manager->releaseAllTextures();
    }

    void setupImGui()
    {
        // 使用light主题
        ImGui::StyleColorsLight();
        ImGuiStyle *style = &ImGui::GetStyle();
        ImVec4 *colors = style->Colors;
        colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 0.9f);        // 使背景色有一点透明
        colors[ImGuiCol_Button] = ImVec4(248/255.0f, 181/255.0f, 81/255.0f, 0.9f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(255/255.0f, 244/255.0f, 92/255.0f, 0.9f);
        colors[ImGuiCol_ButtonActive] = ImVec4(241/255.0f, 145/255.0f, 73/255.0f, 0.9f);
        // window设置
        style->WindowRounding = 0.0f;       // 直角边框
        style->WindowBorderSize = 1.0f;
        style->WindowTitleAlign.x = 0.5f;   // 设置UI标题居中
        style->WindowPadding = ImVec2(70.0f,20.0f);
        // 滚动条设置
        style->ScrollbarSize = 20.0f;
        style->ScrollbarRounding = 10.0f;
        // Frame设置
        style->FrameRounding = 25.0f;
        style->FrameBorderSize = 1.0f;
        // item设置
        style->ItemSpacing = ImVec2(20.0f, 20.0f);
    }

    void showMenu()
    {
        glm::vec2 wSize = Game::getInstance()->getWindowSize();
        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoResize;
        window_flags |= ImGuiWindowFlags_NoCollapse;
        bool *p_open = NULL; // No close button
        float width = 640, height = 480;
        ImGui::Begin("Menu", p_open, window_flags);
        ImGui::SetWindowSize(ImVec2(width, height));
        ImGui::SetWindowPos(ImVec2((wSize.x - width) * 0.5f, (wSize.y - height) * 0.5f));
        ImGui::Text("单击任意选项查看测试：");
        if(ImGui::Button("01. Graphical User Interface (ImGui)",ImVec2(500,30)))
            Game::getInstance()->replaceScene(new Test01(this, "01. Graphical User Interface (ImGui)"),false);
        if(ImGui::Button("02. Graphical User Interface (builtin)",ImVec2(500,30)))
            Game::getInstance()->replaceScene(new Test02(this, "02. Graphical User Interface (builtin)"),false);
        if(ImGui::Button("03. Sprite Animation",ImVec2(500,30)))
            Game::getInstance()->replaceScene(new Test03(this, "03. Sprite Animation"),false);
        if(ImGui::Button("04. empty",ImVec2(500,30)));
        if(ImGui::Button("05. empty",ImVec2(500,30)));
        if(ImGui::Button("06. empty",ImVec2(500,30)));
        if(ImGui::Button("07. empty",ImVec2(500,30)));
        if(ImGui::Button("08. empty",ImVec2(500,30)));
        if(ImGui::Button("09. empty",ImVec2(500,30)));
        if(ImGui::Button("10. empty",ImVec2(500,30)));
        ImGui::End();
    }

    virtual void update()
    {
        Scene::update();
        showMenu();
        // 缓缓旋转logo
        logo->setRotation(-Game::getInstance()->getTime()*0.314159f);
    }
};


class SceneLoading : public Scene
{
public:
    Sprite* logo;
    Label* hint;
    bool loadComplete;
    SceneLoading()
    {
        ResourceManager::getInstance()->loadTexture("ginkgo_logo_1","res/ginkgo_logo_1.png");

        // 设置黑色背景
        setBackgroundColor(glm::vec4(0.1f,0.1f,0.1f,0.0f));
        // 获取游戏窗口的尺寸(画面的尺寸，不包含标题栏和边框)
        glm::vec2 wSize = Game::getInstance()->getWindowSize();
        logo = new Sprite("ginkgo_logo_1");
        addChild(logo);
        logo->setPosition(wSize.x * 0.5f, wSize.y * 0.66f);
        loadComplete = false;
        // 载入字体先
        ImGuiIO &io = ImGui::GetIO();// ImGui use another ttf file
        io.Fonts->AddFontFromFileTTF("res/SourceHanSansSC-Bold.ttf", 16,NULL,io.Fonts->GetGlyphRangesChinese());
        ResourceManager::getInstance()->loadFontTTF("default", "res/SourceHanSansSC-Bold.ttf");
        FontStyle style;
        style.color = vec4(1.0f,1.0f,1.0f,1.0f);
        hint = new Label("Loading...00%",style);
        addChild(hint);
        hint->setPosition((wSize.x - hint->getContainSize().x) * 0.5f, wSize.y * 0.33f);
    }
    virtual ~SceneLoading()
    {

    }
    virtual void update()
    {
        Scene::update();

        static int step = 1;
        static float bg = 0.0f;
        if(!loadComplete)
        {
            char hintstr[20];
            sprintf(hintstr, "Loading...%02d%%",(step-1)*100/11);
            hint->setText(hintstr);
            loadResource(step++);
        }
        else
        {
            bg+=1.0f*Game::getInstance()->getDeltaTime();
            setOpacity(1.0f - bg);
            if(bg>=1.0f)
            {
                setBackgroundColor(vec4(1.0f,1.0f,1.0f,1.0f));
                Game::getInstance()->replaceScene(new SceneWelcome());
            }
        }
    }

    void loadResource(int step)
    {
        Sleep(100);// 给点延时感觉好像资源好多的样子
        // 这个做法就很愚蠢了，但是鉴于还没有做异步这块，先将就吧。。
        auto manager = ResourceManager::getInstance();
        char path[64];
        switch (step) {
        case 1:
            // welcome
            manager->loadTexture("btn_normal", "res/btn_normal.png");
            break;
        case 2:
            manager->loadTexture("btn_pressed", "res/btn_pressed.png");
            break;
        case 3:
            manager->loadTexture("btn_hover", "res/btn_hover.png");
            break;
        case 4:
            manager->loadTexture("logo", "res/logo.png");
            break;
        case 5:
            // Test02
            manager->loadTexture("btn1_normal", "res/btn1_normal.png");
            break;
        case 6:
            manager->loadTexture("btn1_pressed", "res/btn1_pressed.png");
            break;
        case 7:
            // Test03
            for(int i = 0;i<20;i++)
            {
                sprintf(path,"res/k/idle%04d.png",i);
                manager->loadTexture(path,path,false);
            }
            break;
        case 8:
            for(int i = 20;i<40;i++)
            {
                sprintf(path,"res/k/idle%04d.png",i);
                manager->loadTexture(path,path,false);
            }
        case 9:
            for(int i = 0;i<12;i++)
            {
                sprintf(path,"res/k/walk%04d.png",i);
                manager->loadTexture(path,path,false);
            }
            break;
        case 10:
            for(int i = 0;i<8;i++)
            {
                sprintf(path,"res/k/run%04d.png",i);
                manager->loadTexture(path,path,false);
            }
        case 11:
            manager->loadTexture("wasd","res/wasd.png",false);
            break;
        default:
            this->loadComplete = true;
            cout << "Resources loaded completed!"<<endl;
            break;
        }
    }
};
