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
        // 预先载入资源
        loadResource();
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
    }

    void setupImGui()
    {
        ImGuiIO &io = ImGui::GetIO();
        io.Fonts->AddFontFromFileTTF("res/SourceHanSansSC-Bold.ttf", 16,NULL,io.Fonts->GetGlyphRangesChinese());
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

    void loadResource()
    {
        auto manager = ResourceManager::getInstance();
        manager->loadTexture("btn_normal", "res/btn_normal.png");
        manager->loadTexture("btn_pressed", "res/btn_pressed.png");
        manager->loadTexture("btn_hover", "res/btn_hover.png");
        manager->loadTexture("logo", "res/logo.png");
        manager->loadFontTTF("default", "res/SourceHanSansSC-Bold.ttf");
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
            Game::getInstance()->replaceScene(new Test01(this),false);
        if(ImGui::Button("02. Graphical User Interface (builtin)",ImVec2(500,30)))
            Game::getInstance()->replaceScene(new Test02(this),false);
        if(ImGui::Button("03. Sprite Animation",ImVec2(500,30)))
            Game::getInstance()->replaceScene(new Test03(this),false);
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
