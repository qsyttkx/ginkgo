#pragma once
#include <ginkgo.h>
#include <iostream>
#include "test.h"

using namespace glm;
using namespace std;

class SceneWelcome;

class Test06 : public Test
{
public:
    Test06(Scene* menu, string titleString);
    virtual ~Test06();
    virtual void update();
private:
    void testShader(Shader &s, vec2 pos, string hint);
    Shader shaders[4];
};
