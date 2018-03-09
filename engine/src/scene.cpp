#include <scene.h>
#include <ginkgo.h>

using namespace glm;

Scene::Scene()
{
    defaultCamera = new Camera();
    defaultCamera->name = "defaultCamera";
    defaultCamera->setPosition(0.0f,0.0f,100.0f);
    this->addChild(defaultCamera);

    setBackgroundColor(vec4(0.0f));
}

Scene::~Scene()
{
}

void Scene::update()
{
    glClear(GL_COLOR_BUFFER_BIT);
    defaultCamera->updateCameraVectors();
    defaultCamera->setProjectionAndView(Shader::basicDiffuse);
}

void Scene::setBackgroundColor(vec4 bg)
{
    backgroundColor = bg;
    glClearColor(bg.r, bg.g, bg.b, bg.a);
}

vec4 Scene::getBackgroundColor()
{
    return backgroundColor;
}
