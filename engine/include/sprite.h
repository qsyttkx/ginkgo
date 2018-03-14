#pragma once

#include <node.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <resource.h>

class Sprite : public Node
{
  public:
    Sprite();
    Sprite(std::string textureKey);
    virtual ~Sprite();
    virtual void update();

    // 设置锚点
    void setAnchor(glm::vec2 anchor);
    // 设置锚点
    void setAnchor(float x, float y);
    // 取得锚点
    glm::vec2 getAnchor();

    // 设置纹理
    void setTexture(std::string textureKey);
    void setTexture(Texture texture);
    // 获取纹理
    Texture getTexture();
    // 取得纹理大小
    glm::vec2 getTextureSize();
    // 设置混合函数
    void setBlendFunc(unsigned int func1, unsigned int func2);


    // 初始化精灵的顶点坐标数据，所有的精灵、图片，都是使用这6个顶点数据，
    // 然后用不同的Model矩阵来拉伸适配。这样可能可以节省一些顶点缓存资源？
    static void generateVertices();
    // 删除精灵的顶点坐标数据，会在程序将要结束时调用。
    static void deleteVertices();
  protected:
    // 锚点，默认为中心(0.5f,0.5f)
    glm::vec2 anchor;
    // 模型矩阵
    glm::mat4 model;
    // 顶点数组对象、顶点缓存对象
    static GLuint VAO, VBO;
    // 混合函数
    GLuint blendfunc1, blendfunc2;
    // 显示纹理
    Texture texture;
    void updateModelMatrix();
};
