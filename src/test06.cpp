#include "test06.h"

Test06::Test06(Scene* menu, string titleString):Test(menu,titleString)
{
    name = "Test06";
    glm::vec2 wSize = Game::getInstance()->getWindowSize();
    // 黑色背景
    setBackgroundColor(vec4(0));
    title->setFontStyle(FontStyle(32,vec4(1.0f)));

    testShader(Shader::basicDiffuse, wSize*0.5f + vec2(-400,0), "basicDiffuse");
    shaders[0] = Shader("res/shaders/general.vs","res/shaders/binaryzation.fs");
    testShader(shaders[0], wSize*0.5f + vec2(-200,0), "binaryzation");
    shaders[1] = Shader("res/shaders/general.vs","res/shaders/blur.fs");
    testShader(shaders[1], wSize*0.5f + vec2(0,0), "blur");
    shaders[2] = Shader("res/shaders/general.vs","res/shaders/gray.fs");
    testShader(shaders[2], wSize*0.5f + vec2(200,0), "gray");
    shaders[3] = Shader("res/shaders/general.vs","res/shaders/wave.fs");
    testShader(shaders[3], wSize*0.5f + vec2(400,0), "wave");
}

Test06::~Test06()
{
}

void Test06::update()
{
    Test::update();
    // 设置各个着色器的uniform
    for(int i = 0;i<sizeof(shaders)/sizeof(*shaders);++i)
    {
        defaultCamera->setProjectionAndView(&shaders[i]);
        shaders[i].setFloat("tm",Game::getInstance()->getTime());
    }

}

void Test06::testShader(Shader &s, vec2 pos, string hint)
{
    Sprite* yaya = new Sprite("yaya");
    addChild(yaya);
    yaya->setShader(&s);
    yaya->setPosition(pos);
    FontStyle style(16,vec4(1.0f));
    Label* lbl = new Label(hint,style);
    addChild(lbl);
    lbl->setPosition(pos-vec2(lbl->getContainSize().x*0.5f,120));
}
