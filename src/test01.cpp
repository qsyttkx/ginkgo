#include "test01.h"
#include "welcome.h"

Test01::Test01(Scene* menu)
{
    name = "Test01";
    menuScene = menu;
    // 设置白色背景
    setBackgroundColor(vec4(1.0f, 1.0f, 1.0f, 1.0f));
    // 获取游戏窗口的尺寸(画面的尺寸，不包含标题栏和边框)
    glm::vec2 wSize = Game::getInstance()->getWindowSize();
    // 初始化按钮
    btn_back = new Button(this, "btn_normal", "btn_pressed", "btn_hover");
    addChild(btn_back);
    btn_back->setText("返回", FontStyle(18));
    btn_back->onClick = [=](int key, int mods) {
        // 设置回白色背景
        setBackgroundColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        // 返回菜单
        Game::getInstance()->replaceScene(menu);
    };
    // 为节点设置位置的z值可以影响渲染次序，z值越高的越先渲染
    btn_back->setPosition(wSize.x - 75.0f, 50.0f, 1);
    // 初始化标题标签
    title = new Label("01. Ginkgo Graphical User Interface Test (ImGui)", FontStyle(32));
    addChild(title);
    title->setPosition((wSize.x - title->getContainSize().x) / 2, wSize.y - 50.0f, 1.0f);

    show_demo_window = true;
    show_another_window = false;
    clear_color = vec4(1.0f,1.0f,0.94f,1.0f);
}

void Test01::update()
{
    Scene::update();
    // 1. Show a simple window.
    // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets automatically appears in a window called "Debug".
    {
        static float f = 0.0f;
        ImGui::Text("Hello, world!");                           // Some text (you can use a format string too)
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float as a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats as a color
        if (ImGui::Button("Demo Window"))                       // Use buttons to toggle our bools. We could use Checkbox() as well.
            show_demo_window ^= 1;
        if (ImGui::Button("Another Window"))
            show_another_window ^= 1;
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        setBackgroundColor(clear_color);
    }

    // 2. Show another simple window. In most cases you will use an explicit Begin/End pair to name the window.
    if (show_another_window)
    {
        ImGui::Begin("Another Window", &show_another_window);
        ImGui::Text("Hello from another window!");
        ImGui::End();
    }

    // 3. Show the ImGui demo window. Most of the sample code is in ImGui::ShowDemoWindow().
    if (show_demo_window)
    {
        ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver); // Normally user code doesn't need/want to call this because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
        ImGui::ShowDemoWindow(&show_demo_window);
    }
}
