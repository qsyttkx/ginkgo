#define EXPORT
#include <macros.h>
#include <scene.h>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <ginkgo.h>

using namespace ginkgo;
using namespace glm;

Scene::Scene()
{
    auto config = Game::getConfigurations();
    // 配置摄像机
    mainCamera = new Camera(this, vec3(0, 0, config.height * 1.2071f));
    uiCamera = new Camera(this, vec3(0,0, config.height / 0.414f));
    uiCamera->projectionMatrix = ortho(0.0f, (float)config.width, 0.0f, (float)config.height, 0.1f, config.height / 0.414f + 1000.0f);

    // 设置背景色
    backgroundColor = vec3(0.0f);

    ui = new Node();
    ui->name = "GINKGO_ui";

    // 启用一些OpenGL的功能
    glEnable(GL_BLEND);

    // 设置默认的混合函数
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Scene::~Scene()
{
    delete(ui);
}

void Scene::update(float dt)
{
    Node::update(dt);

    renderHeader();

    mainCamera->updateCameraVectors();
    glViewport(0, 0, Game::getConfigurations().width, Game::getConfigurations().height);

    // 默认我们使用最简单的着色器，只有贴图没有光照
    Shader shader = Shader::basicDiffuse;
    //shader.use();

    // 清除缓冲区
    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // 渲染场景
    shader.setMat4("projection", mainCamera->projectionMatrix);
    shader.setMat4("view", mainCamera->getViewMatrix());

    renderChildren();

    // 渲染UI
    glDisable(GL_DEPTH_TEST);
    auto config = Game::getConfigurations();
    shader.setMat4("projection", uiCamera->projectionMatrix);
    shader.setMat4("view", uiCamera->getViewMatrix());
    ui->renderHeader();
    ui->update(dt);
    ui->renderChildren();

}
