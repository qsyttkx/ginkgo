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
    // �ͷ����е��ӽڵ�
    removeAllChildren(true);
    // �Ӹ��ڵ���ӽڵ����Ƴ�
    removedFromParent();
    // ��ӡ�ͷ���Ϣ
    if (name.length() == 0)
        cout << "[0x" << hex << this << "] has been released." << endl;
    else
        cout << "[" << name << "] has been released." << endl;
}

void Node::addChild(Node* c)
{
    // �����ӽڵ�
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
            // ��ȫ��ɾ����Ա��c++11֧��erase�������ر�ɾ������һ���ڵ�
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

// �����ʣ���֪���Բ��԰�����
vec3 Node::globalRotation()
{
    vec3 protation = parent ? parent->rotation : vec3(0);
    return protation + rotation;
}

// δ��ɣ�������
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
    // ���õ�����
    float time = (float)glfwGetTime();
    update(time - lastTime);
    lastTime = time;

    // ����transform
    mat4 translationM = translate(mat4(), position);
    // ŷ������ʽ����ת�����ǰ�x->y->z��˳������ת��
    mat4 rotationM = eulerAngleXYZ(rotation.x, rotation.y, rotation.z);
    mat4 scalingM = scale(mat4(), scaling);
    transform = translationM*rotationM*scalingM;

    // ����parent's global transform
    parentsGlobalTransform = parent ? parent->getGlobalTransform() : mat4();

    // ����global transform
    globalTransform = parentsGlobalTransform * transform;

    // Ĭ������ʹ����򵥵���ɫ����ֻ����ͼû�й���
    Shader::basicDiffuse.use();
    // ����model����
    mat4 model = globalTransform;
    Shader::basicDiffuse.setMat4("model", model);
    // ��children��zֵ����
    children.sort(cmp);
}

void Node::renderChildren()
{
    // ������Ⱦ�ӽڵ�
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
    // 2D�������ô����ֱ�Ӱ�����zֵ��������ι�ϵ
    return this->position.z < n.position.z;
#else
    if (this->shouldSort && !n.shouldSort)
    {
        // ���������С��������Ⱦ
        return false;
    }
    else if (!this->shouldSort && n.shouldSort)
    {
        return true;
    }
    else if (!this->shouldSort && !n.shouldSort)
    {
        // ���ڶ�������������ǲ��ܴ�С
        return false;
    }
    else
    {
        //���ڶ�Ҫ����ģ�������Ҫ������룬�����Խ����Խ��
        vec3 cameraPos = this->getPositionOfRootCamera();
        float lengthThis = length(this->globalPosition() - cameraPos);
        float lengthn = length(n.globalPosition() - cameraPos);
        return lengthThis > lengthn;
}
#endif // GINKGO_SORT_BY_Z_INDEX

}