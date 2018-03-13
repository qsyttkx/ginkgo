#include <node.h>
#include <component.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/euler_angles.hpp>

using namespace glm;
using namespace std;

Node::Node()
{
    parent = nullptr;
    position = vec3(0.0f);
    scale = vec3(1.0f);
    rotation = vec3(0.0f);
    opacity = 1.0f;
    isEnabled = true;
    showReleaseInfo = true;
}

Node::~Node()
{
    // 释放所有的子节点
    removeAllChildren(true);
    // 从父节点中移除
    removedFromParent();

    if(showReleaseInfo)
    {
        if (name.length() == 0)
            cout << "[0x" << hex << this << "] has been released." << endl;
        else
            cout << "[" << name << "] has been released." << endl;
    }
}

void Node::setPosition(glm::vec2 pos)
{
    position.x = pos.x;
    position.y = pos.y;
}

void Node::setPosition(glm::vec3 pos)
{
    position = pos;
}

void Node::setPosition(float x, float y)
{
    position.x = x;
    position.y = y;
}

void Node::setPosition(float x, float y, float z)
{
    position.x = x;
    position.y = y;
    position.z = z;
}

glm::vec2 Node::getPosition()
{
    return vec2(position.x, position.y);
}

glm::vec3 Node::getPosition3()
{
    return position;
}

glm::vec2 Node::getGlobalPosition()
{
    vec4 gpos = globalTransform*vec4(0.0f);
    return vec2(gpos.x, gpos.y);
}

glm::vec3 Node::getGlobalPosition3()
{
    vec4 gpos = globalTransform*vec4(0.0f);
    return vec3(gpos.x, gpos.y, gpos.z);
}

void Node::setScale(glm::vec2 s)
{
    scale.x = s.x;
    scale.y = s.y;
}

void Node::setScale(glm::vec3 s)
{
    scale.x = s.x;
    scale.y = s.y;
    scale.z = s.z;
}

void Node::setScale(float s)
{
    scale.x = s;
    scale.y = s;
    scale.z = s;
}

void Node::setScale(float sx, float sy)
{
    scale.x = sx;
    scale.y = sy;
}

void Node::setScale(float sx, float sy, float sz)
{
    scale.x = sx;
    scale.y = sy;
    scale.z = sz;
}

glm::vec2 Node::getScale2()
{
    return vec2(scale.x, scale.y);
}

glm::vec3 Node::getScale3()
{
    return scale;
}

void Node::setRotation(glm::vec3 rot)
{
    rotation.x = rot.x;
    rotation.y = rot.y;
    rotation.z = rot.z;
}

void Node::setRotation(float rad)
{
    rotation.z = rad;
}

void Node::setRotation(float x, float y, float z)
{
    rotation.x = x;
    rotation.y = y;
    rotation.z = z;
}

float Node::getRotation()
{
    return rotation.z;
}

glm::vec3 Node::getRotation3()
{
    return rotation;
}

void Node::setOpacity(float o)
{
    if (o < 0.0f)
    {
        opacity = 0.0f;
    }
    else if (o > 1.0f)
    {
        opacity = 1.0f;
    }
    else
    {
        opacity = o;
    }
}

float Node::getOpacity()
{
    return opacity;
}

// 获取父节点
Node *Node::getParent()
{
    return parent;
}

// 添加子节点
void Node::addChild(Node *n)
{
    if (n)
    {
        children.push_back(n);
        n->_setParent(this);
    }
    else
    {
        cerr << "Error: Tring to add a NULL Node." << endl;
    }
}

// 获取子节点集合
std::list<Node *> Node::getChildren()
{
    return children;
}

// 移除指定节点，参数2为true时会释放该节点的内存
void Node::removeChild(Node *n, bool release)
{
    for (auto iter = children.begin(); iter != children.end(); ++iter)
    {
        if ((*iter) == n)
        {
            children.erase(iter);
            if (release)
            {
                delete (n);
            }
            break;
        }
    }
}

// 移除所有节点，参数为true时会释放所有节点的内存
void Node::removeAllChildren(bool release)
{
    if (release)
    {
        for (list<Node *>::iterator i = children.begin(); i != children.end();)
        {
            Node *child = *i;
            // 安全的删除成员，c++11支持erase方法返回被删除的下一个节点
            i = children.erase(i);
            delete (child);
        }
    }
    else
    {
        children.clear();
    }
}

// 从父节点中移除本节点
void Node::removedFromParent()
{
    if (parent)
    {
        parent->removeChild(this);
    }
}

void Node::addComponent(std::string key, Component* comp)
{
    if(components.find(key)!=components.end())
    {
        cerr<<"Failed to add component, the key is conflict!"<<endl;
        return;
    }
    comp->host = this;
    components.insert(make_pair(key,comp));
}

Component* Node::getComponent(string key)
{
    auto iter = components.find(key);
    if(iter==components.end())
    {
        return nullptr;
    }
    else
    {
        return (*iter).second;
    }
}

void Node::removeComponent(string key)
{
    if(components.find(key)==components.end())
    {
        cerr<<"Failed to remove component, can't find it!"<<endl;
        return;
    }
    components.erase(key);
}

void Node::update()
{
    // xxx
}

bool cmp(const Node* a, const Node*b)
{
    return (*a) < (*b);
}

void Node::traverse()
{
    // 更新Transform等属性
    updateTransform();

    // 先执行自己的任务
    update();
    // 调用所有组件
    for (auto iter = components.begin(); iter != components.end(); ++iter)
    {
        (*iter).second->update();
    }

    // 给子节点按z值排序
    children.sort(cmp);
    // 遍历子节点
    for (auto iter = children.begin(); iter != children.end(); ++iter)
    {
        // 若该子节点未启用则不管他
        if ((*iter)->isEnabled == false)
            continue;
        (*iter)->traverse();
    }

    // 调用所有组件
    for (auto iter = components.begin(); iter != components.end(); ++iter)
    {
        (*iter).second->updateLater();
    }
}

Shader& Node::getShader()
{
    if(shader.getID()!=0)
        return shader;
    else if (getParent()!=nullptr)
        return getParent()->getShader();
    else return Shader::basicDiffuse;
}

void Node::setShader(Shader& shader)
{
    this->shader = shader;
}

// 更新Transform等属性
void Node::updateTransform()
{
    // 合成透明度
    parentsGlobalOpacity = parent ? parent->globalOpacity : 1.0f;
    globalOpacity = parentsGlobalOpacity * opacity;

    // 更新Transform
    mat4 translationM = translate(mat4(), position);
    // 欧拉角形式的旋转，我们按x->y->z的顺序来旋转吧
    mat4 rotationM = eulerAngleXYZ(rotation.x, rotation.y, rotation.z);
    mat4 scalingM = glm::scale(mat4(), scale);
    transform = translationM*rotationM*scalingM;
    // 更新parent's global transform
    parentsGlobalTransform = parent ? parent->globalTransform : mat4();
    // 更新global transform
    globalTransform = parentsGlobalTransform * transform;
}

void Node::_setParent(Node *p)
{
    parent = p;
}

bool Node::operator<(const Node &n) const
{
    // 2D情况，我们直接按照其z值来决定层次关系（摄像机在z值高的地方）
    return this->position.z < n.position.z;
}
