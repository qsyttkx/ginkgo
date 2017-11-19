#define EXPORT
#include <macros.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
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

mat4 Node::getTransform() const
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

vec3 Node::globalPosition() const
{
	if (parent)
		return parent->globalPosition() + position;
	else
		return position;
}

vec3 Node::globalRotation() const
{
	if (parent)
		return parent->globalRotation() + rotation;
	else
		return rotation;
}
vec3 Node::globalScaling() const
{
	if (parent)
		return parent->globalScaling()*scaling;
	else
		return scaling;
}

mat4 Node::getGlobalTransform() const
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
	return (*a) < (*b);
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