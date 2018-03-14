#include <scene.h>
#include <ginkgo.h>

using namespace glm;

Scene::Scene()
{
    defaultCamera = new Camera();
    defaultCamera->name = "defaultCamera";
    defaultCamera->setPosition(0.0f,0.0f,100.0f);
    this->addChild(defaultCamera);

    imGuiRenderer = new ImGuiRenderer();
    addComponent("_imgui",imGuiRenderer);

    setBackgroundColor(vec4(0.0f));
}

Scene::~Scene()
{
    delete(imGuiRenderer);
    mouseEventListeners.clear();
    keyboardEventListeners.clear();
}

void Scene::update()
{
    Node::update();

    ImGui_ImplGlfwGL3_NewFrame();

    int display_w, display_h;
    glfwGetFramebufferSize(Game::getInstance()->getGLFWwindow(), &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClear(GL_COLOR_BUFFER_BIT);
    defaultCamera->updateCameraVectors();
    defaultCamera->setProjectionAndView(&Shader::basicDiffuse);
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


ImGuiRenderer::ImGuiRenderer()
{

}

ImGuiRenderer::~ImGuiRenderer()
{

}

void ImGuiRenderer::updateLater()
{
    ImGui::Render();
}
