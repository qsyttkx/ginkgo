#include <sprite.h>
#include <glm/gtc/matrix_transform.hpp>

GLuint Sprite::VAO = 0;
GLuint Sprite::VBO = 0;

using namespace std;
using namespace glm;

Sprite::Sprite()
{
    texture.id = 0;
    model = mat4();
    anchor = vec2(0.5f, 0.5f);
    blendfunc1 = GL_SRC_ALPHA;
    blendfunc2 = GL_ONE_MINUS_SRC_ALPHA;
}

Sprite::Sprite(string textureKey) : Sprite()
{
    setTexture(textureKey);
}

Sprite::~Sprite()
{
}

void Sprite::update()
{
    Node::update();

    // 如果当前没有纹理则不渲染
    if (texture.id == 0)
    {
        return;
    }

    // 选用着色器，若未指定则使用父节点的着色器
    Shader *shader = getShader();
    shader->use();

    // 启用混合（达到半透明、叠加等效果）
    glEnable(GL_BLEND);
    glBlendFunc(blendfunc1, blendfunc2);

    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture.id);
    // 设置纹理
    shader->setInt("texture_diffuse1", 0);
    // 设置model矩阵
    shader->setMat4("model", globalTransform * model);
    // 设置透明度
    shader->setFloat("node_opacity", globalOpacity);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindTexture(GL_TEXTURE_2D, 0); 
}

void Sprite::setAnchor(vec2 anchor)
{
    this->anchor = anchor;
    updateModelMatrix();
}

void Sprite::setAnchor(float x, float y)
{
    this->anchor = vec2(x, y);
    updateModelMatrix();
}

vec2 Sprite::getAnchor()
{
    return this->anchor;
}

void Sprite::setTexture(string textureKey)
{
    texture = ResourceManager::getInstance()->getTexture(textureKey);
    updateModelMatrix();
}

void Sprite::setTexture(Texture texture)
{
    this->texture = texture;
    updateModelMatrix();
}

Texture Sprite::getTexture()
{
    return texture;
}

vec2 Sprite::getTextureSize()
{
    return vec2(texture.width,texture.height);
}

void Sprite::generateVertices()
{
    float vertices[] =
        {// 这样设置顶点位置可以使得锚点在图片中心
         // 顶点位置             纹理坐标
         -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
         -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,

         -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f, 0.5f, 0.0f, 1.0f, 1.0f};

    // 生成VAO, VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glBindVertexArray(0);
}

void Sprite::deleteVertices()
{
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void Sprite::updateModelMatrix()
{
    mat4 mTranslate = translate(mat4(), vec3((0.5f - anchor.x) * texture.width, (0.5f - anchor.y) * texture.height, 0.0f));
    model = glm::scale(mTranslate, vec3(texture.width, texture.height, 1.0f));
}
