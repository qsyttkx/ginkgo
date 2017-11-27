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
    mainCamera = new Camera(this, vec3(0, 0, 500.0f));
    // 设置背景色
    backgroundColor = vec3(0.0f);

    // 启用一些OpenGL的功能
    glEnable(GL_BLEND);

    // 设置默认的混合函数
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
    mat4 projection = mainCamera->projectionMatrix;
    mat4 view = mainCamera->getViewMatrix();
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);

    renderChildren();
}
