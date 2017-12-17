#define EXPORT

#include <macros.h>
#include <scene.h>
#include <glm/gtc/matrix_transform.hpp>
#include <ginkgo.h>

using namespace ginkgo;
using namespace glm;

Scene::Scene()
{
    // 设置背景色
    backgroundColor = vec3(0.0f);

    float width = (float)Game::getConfigurations().width;
    float height = (float)Game::getConfigurations().height;
    matProjection = ortho(0.0f, (float)width, 0.0f, (float)height, 0.1f, height / 0.414f + 1000.0f);
    vec3 position(0, 0, height * 1.2071f);
    vec3 center(0, 0, 0.0f);
    vec3 up(0, 1, 0);
    matView = glm::lookAt(position, center, up);

    // 设置默认层
    defaultLayer = new Layer(this, width, height);
}

Scene::~Scene()
{
}

void Scene::update(float dt)
{
    Node::update(dt);

    // 先执行层的渲染
    auto children = getChildren();
    for (auto iter = children.begin(); iter != children.end(); ++iter)
    {
        if (dynamic_cast<Layer*>(*iter))
        {
            dynamic_cast<Layer*>(*iter)->renderToTexture(dt);
        }
    }

    // 拼合层
    renderHeader();
    glViewport(0, 0, Game::getConfigurations().width, Game::getConfigurations().height);
    // 清除缓冲区
    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // 遍历渲染子节点
    for (auto iter = children.begin(); iter != children.end(); iter++)
    {
        // 如果此子节点不可见则不渲染它
        if ((*iter)->isEnabled == false)continue;
        auto layer = dynamic_cast<Layer*>(*iter);
        if (layer)
        {
            layer->shader->use();
            layer->shader->setMat4("projection", matProjection);
            layer->shader->setMat4("view", matView);
            layer->renderHeader();
            layer->update(dt);
        }
        else 
        {
            (*iter)->renderHeader();
            (*iter)->update(dt);
            (*iter)->renderChildren();
        }
    }
}
