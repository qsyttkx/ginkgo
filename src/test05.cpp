#include "test05.h"

Test05::Test05(Scene* menu, string titleString):Test(menu,titleString)
{
    name = "Test05";
    isPlaying = false;
    volume = 0.8f;
    ResourceManager::getInstance()->getMusic("res/music.mp3").setVolume(int(volume*500));
    listener = new MouseEventListener(this);
    listener->buttonCallback = [=](int button, int action, int mods)
    {
        if(button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE)
        {
            auto pos = Game::getInstance()->getMousePosition();
            pos.y = Game::getInstance()->getWindowSize().y - pos.y;
            addChild_later(new TapSprite(pos));
        }
        return false;
    };
    addComponent("mouselistener",listener);
}

Test05::~Test05()
{
    ResourceManager::getInstance()->getMusic("res/music.mp3").stop();
}

void Test05::update()
{
    Test::update();

    // ImGui
    glm::vec2 wSize = Game::getInstance()->getWindowSize();
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoCollapse;
    bool *p_open = NULL; // No close button
    float width = 640, height = 240;
    ImGui::Begin("Music Controller", p_open, window_flags);
    ImGui::SetWindowSize(ImVec2(width, height));
    ImGui::SetWindowPos(ImVec2((wSize.x - width) * 0.5f, wSize.y * 0.3f - height * 0.5f));
    ImGui::Text(ResourceManager::getInstance()->getMusic("res/music.mp3").getFilePath().c_str());
    if(!isPlaying)
    {
        if(ImGui::Button("Play",ImVec2(100,30)))
        {
            ResourceManager::getInstance()->getMusic("res/music.mp3").play();
            isPlaying = true;
        }
    }
    else
    {
        if(ImGui::Button("Pause",ImVec2(100,30)))
        {
            ResourceManager::getInstance()->getMusic("res/music.mp3").pause();
            isPlaying = false;
        }
    }
    ImGui::SameLine();
    if(ImGui::Button("Stop",ImVec2(100,30)))
    {
        ResourceManager::getInstance()->getMusic("res/music.mp3").stop();
        isPlaying = false;
    }
    if(ImGui::SliderFloat("Volume: ",&volume,0.0f,1.0f))
        ResourceManager::getInstance()->getMusic("res/music.mp3").setVolume(int(volume*500));
    ImGui::Text(string("Status: ").append(ResourceManager::getInstance()->getMusic("res/music.mp3").getStatus()).c_str());
    ImGui::Text("左键点击任意地方触发音效");
    ImGui::End();

}

TapSprite::TapSprite(vec2 pos):Sprite("tap")
{
    this->setPosition(pos);
    bornTime = Game::getInstance()->getTime();
    this->setScale(0);
    this->setOpacity(0.5f);
    Music::playSound("res/click.mp3");
}

TapSprite::~TapSprite()
{

}

void TapSprite::update()
{
    Sprite::update();
    float life = Game::getInstance()->getTime() - bornTime;
    this->setScale(sqrt(life)*3.0f);
    this->setOpacity((1.0f-sqrt(life))*0.5f);
    if(life>=1)
    {
        this->getParent()->removeChild_later(this);
    }
}
