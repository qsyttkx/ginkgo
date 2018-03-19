/*Node类，作为场景中大部分对象的基类*/
#pragma once

#include <glm/glm.hpp>
#include <list>
#include <map>
#include <string>
#include <component.h>
#include <shader.h>

class Node
{
  public:
    Node();
    virtual ~Node();

    // 是否启用本节点，默认为是
    bool isEnabled;
    // 节点名字
    std::string name;

    // 设置、获取Node的Transform属性（位移、拉伸、旋转）
    void setPosition(glm::vec2 pos);
    void setPosition(glm::vec3 pos);
    void setPosition(float x, float y);
    void setPosition(float x, float y, float z);
    glm::vec2 getPosition();
    glm::vec3 getPosition3();
    glm::vec2 getGlobalPosition();
    glm::vec3 getGlobalPosition3();
    void setScale(glm::vec2 s);
    void setScale(glm::vec3 s);
    void setScale(float s);
    void setScale(float sx, float sy);
    void setScale(float sx, float sy, float sz);
    glm::vec2 getScale2();
    glm::vec3 getScale3();
    void setRotation(glm::vec3 rot);
    void setRotation(float rad);
    void setRotation(float x, float y, float z);
    float getRotation();
    glm::vec3 getRotation3();

    // 设置、获取透明度属性
    void setOpacity(float o);
    float getOpacity();

    // 获取父节点
    Node *getParent();
    // 添加子节点
    void addChild(Node *n);
    // 获取子节点集合
    std::list<Node *> getChildren();
    // 移除指定节点，参数2为true时会释放该节点的内存
    void removeChild(Node *n, bool release = false);
    // 移除所有节点，参数为true时会释放所有节点的内存
    void removeAllChildren(bool release = false);
    // 从父节点中移除本节点
    void removedFromParent();
    // 添加一个组件
    void addComponent(std::string key, Component* comp);
    // 获取一个组件
    Component* getComponent(std::string key);
    // 移除一个组件
    void removeComponent(std::string key, bool release = false);
    // 清空组件
    void removeAllComponents(bool release = false);

    // 逐帧调度器
    virtual void update();

    // 遍历节点
    virtual void traverse();

    Shader* getShader();
    void setShader(Shader* shader);

    //重写的小于运算符，用于在list中排序以决定渲染顺序
    bool operator<(const Node &n) const;
    // 是否打印释放信息
    bool showReleaseInfo;
  protected:
    // Transform属性
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;
    // 变换矩阵
    glm::mat4 transform;
    // 父节点的全局变换矩阵（相对世界坐标系而言这个节点所在的坐标系）
    glm::mat4 parentsGlobalTransform;
    // 全局变换矩阵
    glm::mat4 globalTransform;

    // 透明度属性
    float opacity;
    // 父节点的合成透明度
    float parentsGlobalOpacity;
    // 合成透明度（实际体现到界面上的透明度）
    float globalOpacity;

    // 更新Transform等属性
    void updateTransform();

    // 节点树
    Node *parent;
    std::list<Node *> children;
    /* 请勿使用此方法！
	/* 此方法只设置了本节点的父节点，而不会在父节点中添加本节点。
	/* 要连接两个节点，请使用addChild()方法。*/
    void _setParent(Node *p);
    // 组件集
    std::map<std::string, Component*> components;
private:
    // 所用的着色器
    Shader *shader;
};
