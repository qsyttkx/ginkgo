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
	// �ͷ����е��ӽڵ�
	removeAllChildren(true);
	// �Ӹ��ڵ���ӽڵ����Ƴ�
	removedFromParent();
	// ��ӡ�ͷ���Ϣ
	cout << "\"" << name << "\" has been released." << endl;
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

mat4 Node::getTransform() const
{
	mat4 transform;
	transform = scale(transform, scaling);
	// ŷ������ʽ����ת�����ǰ�x->y->z��˳������ת��
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
	// ŷ������ʽ����ת�����ǰ�x->y->z��˳������ת��
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
	// Ĭ������ʹ����򵥵���ɫ����ֻ����ͼû�й���
	Shader::basicDiffuse.use();
	// ����model����
	mat4 model = getGlobalTransform();
	Shader::basicDiffuse.setMat4("model", model);
	// ��children��zֵ����
	children.sort(cmp);

	// ���õ�����
	float time = (float)glfwGetTime();
	update(time - lastTime);
	lastTime = time;
}

void Node::renderChildren()
{
	// ������Ⱦ�ӽڵ�
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