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
    mainCamera = new Camera(this, vec3(0, 0, Game::getConfigurations().height / 0.414f));
    // ���ñ���ɫ
    backgroundColor = vec3(0.0f);

    // ����һЩOpenGL�Ĺ���
    glEnable(GL_BLEND);

    // ����Ĭ�ϵĻ�Ϻ���
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Scene::~Scene()
{
    //...
}

void Scene::render()
{
    renderHeader();

    mainCamera->updateCameraVectors();
    glViewport(0, 0, Game::getConfigurations().width, Game::getConfigurations().height);

    // Ĭ������ʹ����򵥵���ɫ����ֻ����ͼû�й���
    Shader shader = Shader::basicDiffuse;
    //shader.use();

    // ���������
    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    mat4 projection = mainCamera->projectionMatrix;
    mat4 view = mainCamera->getViewMatrix();
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);

    renderChildren();
}
