#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <GLFW/glfw3.h>

#include <node.h>

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
}

Node::~Node()
{
	// 释放所有的子节点
	removeAllChildren(true);
	// 从父节点的子节点中移除
	removedFromParent();
	// 打印释放消息
	cout << "\"" << name << "\" has been released." << endl;
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
			children.erase(iter);
		if (releaseChildren)
		{
			delete(n);
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
	mat4 transform;
	transform = scale(transform, scaling);
	// 欧拉角形式的旋转，我们按x->y->z的顺序来旋转吧
	transform = rotate(transform, rotation.x, vec3(1, 0, 0));
	transform = rotate(transform, rotation.y, vec3(0, 1, 0));
	transform = rotate(transform, rotation.z, vec3(0, 0, 1));
	transform = translate(transform, position);
	return transform;
}

vec3 Node::globalPosition()
{
	if (parent)
		return parent->globalPosition() + position;
	else
		return vec3(0.0f);
}

vec3 Node::globalRotation()
{
	if (parent)
		return parent->globalRotation() + rotation;
	else
		return vec3(0.0f);
}
vec3 Node::globalScaling()
{
	if (parent)
		return parent->globalScaling()*scaling;
	else
		return vec3(1.0f);
}

mat4 Node::getGlobalTransform()
{
	vec3 pscaling = parent ? parent->globalScaling() : vec3(1.0f);
	vec3 protation = parent ? parent->globalRotation() : vec3(0.0f);
	vec3 pposition = parent ? parent->globalPosition() : vec3(0.0f);
	mat4 transform;
	transform = scale(transform, pscaling);
	// 欧拉角形式的旋转，我们按x->y->z的顺序来旋转吧
	transform = rotate(transform, protation.x, vec3(1, 0, 0));
	transform = rotate(transform, protation.y, vec3(0, 1, 0));
	transform = rotate(transform, protation.z, vec3(0, 0, 1));
	transform = translate(transform, pposition);
	return transform*getTransform();
}

void Node::render()
{
	renderHeader();
	renderChildren();
}

bool cmp(const Node* a, const Node*b)
{
	return a->position.z < b->position.z;
}
void Node::renderHeader()
{
	// 默认我们使用最简单的着色器，只有贴图没有光照
	Shader::basicDiffuse.use();
	// 设置model矩阵
	mat4 model = getGlobalTransform();
	Shader::basicDiffuse.setMat4("model", model);
	// 给children按z值排序
	children.sort(cmp);

	// 调用调度器
	float time = (float)glfwGetTime();
	update(time - lastTime);
	lastTime = time;
}

void Node::renderChildren()
{
	// 遍历渲染子节点
	for (auto iter = children.begin(); iter != children.end(); iter++)
	{
		(*iter)->render();
	}
}
