#define EXPORT
#include <macros.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <GLFW/glfw3.h>

#include <node.h>
#include <scene.h>

using namespace ginkgo;
using namespace std;
using namespace glm;

//Node::Node()
//{
//	parent = NULL;
//	init();
//	
//}

Node::Node(Node* parent)
{
    this->setParent(parent);

    position = vec3(0.0f);
    scaling = vec3(1.0f);
    rotation = vec4(0.0f);
    lastTime = (float)glfwGetTime();
    shouldSort = false;
}

Node::~Node()
{
    // 释放所有的子节点
    removeAllChildren(true);
    // 从父节点的子节点中移除
    removedFromParent();
    // 打印释放消息
    if (name.length() == 0)
        cout << "[0x" << hex << this << "] has been released." << endl;
    else
        cout << "[" << name << "] has been released." << endl;
}

void Node::addChild(Node* c)
{
    // 插入子节点
    children.push_back(c);
}

void Node::setParent(Node* p)
{
    parent = p;
    if (p)
    {
        p->addChild(this);
    }
}

Node* Node::getParent()
{
    return parent;
}

list<Node*> Node::getChildren()
{
    return children;
}

void Node::removeChild(Node* n, bool releaseChildren)
{
    for (auto iter = children.begin(); iter != children.end(); iter++)
    {
        if ((*iter) == n)
        {
            children.erase(iter);
            if (releaseChildren)
            {
                delete(n);
            }
            break;
        }
    }
}

void Node::removeAllChildren(bool releaseChildren)
{
    if (releaseChildren)
    {
        for (list<Node*>::iterator i = children.begin(); i != children.end();)
        {
            Node* child = *i;
            // 安全的删除成员，c++11支持erase方法返回被删除的下一个节点
            i = children.erase(i);
            delete(child);
        }
    }
    else
    {
        children.clear();
    }
}

void Node::removedFromParent()
{
    if (parent)
    {
        parent->removeChild(this);
    }
}

mat4 Node::getTransform()
{
    return this->transform;
}

mat4 Node::getGlobalTransform()
{
    return this->globalTransform;
}


vec3 Node::globalPosition()
{
    vec4 gpos = globalTransform * vec4(0);
    return vec3(gpos.x, gpos.y, gpos.z);
}

// 有疑问，不知道对不对啊。。
vec3 Node::globalRotation()
{
    vec3 protation = parent ? parent->rotation : vec3(0);
    return protation + rotation;
}

// 未完成，有问题
//vec3 Node::globalScaling()
//{
//    return vec3(0);
//}

void Node::render()
{
}

bool cmp(const Node* a, const Node*b)
{
    return (*a) < (*b);
}

void Node::renderHeader()
{
    // 调用调度器
    float time = (float)glfwGetTime();
    update(time - lastTime);
    lastTime = time;

    // 更新transform
    mat4 translationM = translate(mat4(), position);
    // 欧拉角形式的旋转，我们按x->y->z的顺序来旋转吧
    mat4 rotationM = eulerAngleXYZ(rotation.x, rotation.y, rotation.z);
    mat4 scalingM = scale(mat4(), scaling);
    transform = translationM*rotationM*scalingM;

    // 更新parent's global transform
    parentsGlobalTransform = parent ? parent->getGlobalTransform() : mat4();

    // 更新global transform
    globalTransform = parentsGlobalTransform * transform;

    // 默认我们使用最简单的着色器，只有贴图没有光照
    Shader::basicDiffuse.use();
    // 设置model矩阵
    mat4 model = globalTransform;
    Shader::basicDiffuse.setMat4("model", model);
    // 给children按z值排序
    children.sort(cmp);
}

void Node::renderChildren()
{
    // 遍历渲染子节点
    for (auto iter = children.begin(); iter != children.end(); iter++)
    {
        (*iter)->renderHeader();
        (*iter)->render();
        (*iter)->renderChildren();
    }
}

vec3 Node::getPositionOfRootCamera() const
{
    if (((Scene*)this)->mainCamera)
    {
        return ((Scene*)this)->mainCamera->globalPosition();
    }
    else if (parent)
    {
        return parent->getPositionOfRootCamera();
    }
    else
    {
        return vec3(0);
    }
}

bool Node::operator<(const Node& n) const
{
#ifdef GINKGO_SORT_BY_Z_INDEX
    // 2D情况，那么我们直接按照其z值来决定层次关系
    return this->position.z < n.position.z;
#else
    if (this->shouldSort && !n.shouldSort)
    {
        // 不用排序的小，优先渲染
        return false;
    }
    else if (!this->shouldSort && n.shouldSort)
    {
        return true;
    }
    else if (!this->shouldSort && !n.shouldSort)
    {
        // 对于都不用排序的我们不管大小
        return false;
    }
    else
    {
        //对于都要排序的，我们需要计算距离，离相机越近的越大
        vec3 cameraPos = this->getPositionOfRootCamera();
        float lengthThis = length(this->globalPosition() - cameraPos);
        float lengthn = length(n.globalPosition() - cameraPos);
        return lengthThis > lengthn;
}
#endif // GINKGO_SORT_BY_Z_INDEX

}