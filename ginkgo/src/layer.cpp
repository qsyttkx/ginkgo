#define EXPORT

#include <ginkgo.h>
#include <macros.h>
#include <layer.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace ginkgo;
using namespace glm;

Layer::Layer(Node* parent, float width, float height) :Node(parent)
{
    if (width == 0)width = (float)Game::getConfigurations().width;
    if (height == 0)height = (float)Game::getConfigurations().height;

    root = new Node(this);

    // 配置摄像机
    camera = new Camera(this, vec3(0, 0, height * 1.2071f));
    // 设置背景色
    backgroundColor = vec4(0.0f);

    this->width = width;
    this->height = height;
    // 绑定顶点数据
    float vertices[] =
    {	// 这样设置顶点位置可以使得锚点在图片左下角
        // 顶点位置						   纹理坐标
        0.0f,  height, 0.0f,    0.0f, 1.0f,
        0.0f, 0.0f, 0.0f,    0.0f, 0.0f,
        width, 0.0f,  0.0f,    1.0f, 0.0f,

        0.0f,  height, 0.0f,    0.0f, 1.0f,
        width, 0.0f,  0.0f,    1.0f, 0.0f,
        width,  height,  0.0f,    1.0f, 1.0f
    };

    // 生成VAO, VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);

    // 创建帧缓冲
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    // 创建纹理附件
    framebuffertexture = Texture(int(width), int(height), GL_RGBA);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebuffertexture.id, 0);
    // 创建渲染缓冲
    glGenRenderbuffers(1, &renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, framebuffertexture.width, framebuffertexture.height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer);
    // 检查帧缓冲状态
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        printf("ERROR::FRAMEBUFFER::Framebuffer is not compelte!\n");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Layer::~Layer()
{
    framebuffertexture.release();
}

void ginkgo::Layer::renderToTexture(float dt)
{
    renderHeader();

    // 渲染到纹理
    camera->updateCameraVectors();
    glViewport(0, 0, int(width), int(height));
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    // 清除缓冲区
    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // 渲染场景
    Shader::basicDiffuse.use();
    Shader::basicDiffuse.setMat4("projection", camera->projectionMatrix);
    Shader::basicDiffuse.setMat4("view", camera->getViewMatrix());

    renderChildren();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Layer::update(float dt)
{
    // 应用纹理到矩形上
    Node::update(dt);
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, framebuffertexture.id);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void ginkgo::Layer::renderHeader()
{
    Node::renderHeader();
}

glm::mat4 ginkgo::Layer::getGlobalTransform()
{
    return glm::mat4();
}
