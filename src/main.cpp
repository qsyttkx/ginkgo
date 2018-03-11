#include <iostream>
#include <ginkgo.h>

#include <Box2D/Box2D.h>

using namespace std;

class SceneWelcome : public Scene
{
public:
    Button *btn1,*btn2;
    Label* hint;
    Sprite* circle;
    Sprite* block1;
    Sprite* block2;

    b2World* world;
    b2Body* circleBody;
    b2Body* block2Body;

    Physics* phy;
    KeyboardEventListener *listener1;

    bool show_demo_window;
    bool show_another_window;
    ImVec4 clear_color;

    SceneWelcome()
    {
        loadResource();

        name = "Welcome";
        setBackgroundColor(glm::vec4(1.0f,1.0f,1.0f,1.0f));

        glm::vec2 wSize = Game::getInstance()->getWindowSize();

        btn1 = new Button("btn_normal", "btn_pressed", "btn_hover");
        addChild(btn1);
        btn1->setText("Start",FontStyle(20));
        btn1->name = "btn1";
        btn1->onClick = [=](int key, int mods) {
            start();
        };
        btn1->setPosition(100.0f,wSize.y - 50.0f,1);

        btn2 = new Button("btn_normal", "btn_pressed", "btn_hover");
        addChild(btn2);
        btn2->setText("Exit(Esc)",FontStyle(20));
        btn2->name = "btn2";
        btn2->onClick = [=](int key, int mods) {
            Game::getInstance()->end();
        };
        btn2->setPosition(100.0f,wSize.y - 80.0f,1);
        listener1 = new KeyboardEventListener();
        listener1->callback = [=](int key, int scancode, int action, int mods)
        {
            // printf("key: %d, scancode: %d, action: %d, mods: %d\n",key,scancode,action,mods);
            fflush(stdout);
            if(key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
            {
                Game::getInstance()->end();
            }
        };
        btn2->addComponent("key",listener1);

        hint = new Label("Ginkgo2 physics test",FontStyle(48));
        addChild(hint);
        hint->setPosition((wSize.x-hint->getContainSize().x)/2,wSize.y - 50.0f,1.0f);

        circle = new Sprite("circle");
        addChild(circle);
        circle->setPosition(200.0f,wSize.y-200.0f);

        block1 = new Sprite("rect");
        block1->setPosition(wSize.x/2,0);
        block1->setScale(wSize.x/300.0f,2.0f/10.0f);
        addChild(block1);

        block2 = new Sprite("rect");
        addChild(block2);
        block2->setPosition(wSize.x/2.0f-block1->getTextureSize().x/2.0f,block1->getTextureSize().y/2.0f+200.0f);
        block2->setRotation(95.0f);
        // box2d

        // Creating a world
        phy = new Physics(glm::vec2(0.0f,-100.0f));
        addComponent("physics",phy);
        world = phy->getWorld();
        phy->running = false;

        // Creating a ground box
        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(wSize.x/20.0f,0);
        b2Body* groundBody = world->CreateBody(&groundBodyDef);
        b2PolygonShape groundBox;
        groundBox.SetAsBox(wSize.x/20.0f,1);
        groundBody->CreateFixture(&groundBox,0.0f);
        groundBodyDef.position.Set(wSize.x/10+1,wSize.y/20);
        groundBody = world->CreateBody(&groundBodyDef);
        groundBox.SetAsBox(1,wSize.y/20);
        groundBody->CreateFixture(&groundBox,0.0f);
        // Creating a DynamicBody
        b2BodyDef circlebodyDef;
        circlebodyDef.type = b2_dynamicBody;
        circlebodyDef.position.Set(circle->getPosition().x/10.0f,circle->getPosition().y/10.0f);
        circleBody = world->CreateBody(&circlebodyDef);
        b2CircleShape dynamicCircle;
        dynamicCircle.m_p.Set(0.0f,0.0f);
        dynamicCircle.m_radius = circle->getTextureSize().x/20;
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicCircle;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.2f;
        fixtureDef.restitution = 0.5f;
        circleBody->CreateFixture(&fixtureDef);
        circleBody->SetLinearVelocity(b2Vec2(35.0f,35.0f));

        // Creating another DynamicBody
        b2BodyDef boxbodyDef;
        boxbodyDef.type = b2_dynamicBody;
        boxbodyDef.position.Set(block2->getPosition().x/10.0f,block2->getPosition().y/10.0f);
        boxbodyDef.angle = glm::radians(block2->getRotation());
        block2Body = world->CreateBody(&boxbodyDef);
        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(block2->getTextureSize().x/20.0f,block2->getTextureSize().y/20.0f);
        b2FixtureDef fixtureDef2;
        fixtureDef2.shape = &dynamicBox;
        fixtureDef2.density = 1.0f;
        fixtureDef2.friction = 0.2f;
        fixtureDef2.restitution = 0.5f;
        block2Body->CreateFixture(&fixtureDef2);

        show_demo_window = true;
        show_another_window = false;
        clear_color.x = 0.8f;
        clear_color.y = 0.8f;
        clear_color.z = 0.8f;
        ImGuiIO& io = ImGui::GetIO();
        io.Fonts->AddFontFromFileTTF("res/BerkshireSwash-Regular.ttf", 18);
        ImGui::StyleColorsLight();
        ImGuiStyle* style = &ImGui::GetStyle();
        ImVec4* colors = style->Colors;
        colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 0.80f);
        style->WindowBorderSize = 1;
    }

    virtual ~SceneWelcome()
    {
        delete(listener1);
        delete(phy);
    }

    void loadResource()
    {
        auto manager = ResourceManager::getInstance();
        manager->loadTexture("btn_normal", "res/btn_normal.png");
        manager->loadTexture("btn_pressed", "res/btn_pressed.png");
        manager->loadTexture("btn_hover", "res/btn_hover.png");
        manager->loadTexture("logo","res/logo.png");
        manager->loadFontTTF("default","res/BerkshireSwash-Regular.ttf");
        manager->loadTexture("circle","res/circle.png");
        manager->loadTexture("rect","res/rect.png");
    }

    void start()
    {
        phy->running = !phy->running;
        if(phy->running)btn1->setText("Pause");
        else btn1->setText("Resume");
    }

    virtual void update()
    {
        Scene::update();

        if(phy->running)
        {
            // simulating
            b2Vec2 position = circleBody->GetPosition();
            float32 angle = circleBody->GetAngle();
            circle->setPosition(position.x*10.0f,position.y*10.0f);
            circle->setRotation(angle*180.0f/3.1415926f);
            position = block2Body->GetPosition();
            angle = block2Body->GetAngle();
            block2->setPosition(position.x*10.0f,position.y*10.0f);
            block2->setRotation(angle*180.0f/3.1415926f);
        }

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

        setBackgroundColor(glm::vec4(clear_color.x, clear_color.y, clear_color.z, clear_color.w));
    }
};

class MyGame : public Game
{
public:
    MyGame() : Game()
    {
        setTitle("Hello my game engine");
        SceneWelcome *welcome = new SceneWelcome();
        replaceScene(welcome);
    }
};

int main()
{
    return MyGame().run();
}
