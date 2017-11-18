#pragma once

#include <list>
#include <string>
#include <glm/glm.hpp>
#include <macros.h>
#include <shader.h>

namespace ginkgo
{
	// �ڵ����
	class DLL Node
	{
	public:
		//Node();
		Node(Node* parent = NULL);
		~Node();
		// ���ø��ڵ�
		void setParent(Node* p);
		// ��ȡ���ڵ�
		Node* getParent();
		// ��ȡ�ӽڵ㼯��
		std::list<Node*> getChildren();
		// �Ƴ�ָ���ӽڵ�
		void removeChild(Node* n, bool releaseChildren = false);
		// �Ƴ������ӽڵ�
		void removeAllChildren(bool releaseChildren = false);
		// �Ӹ��ڵ����Ƴ����ڵ�
		void removedFromParent();
		// �ڵ�����
		std::string name;
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scaling;
		glm::mat4 getTransform();
		glm::vec3 globalPosition();
		glm::vec3 globalRotation();
		glm::vec3 globalScaling();
		glm::mat4 getGlobalTransform();
		// ��Ⱦ�Ľڵ�
		// ����д��render�����У���Ҫ�ڿ�ͷ����renderHeader()��������ɫ���͵�ǰ�ڵ��ģ�;���
		// ���ڽ�β������Ҫ����renderChildren()�����Եݹ���Ⱦ���ӽڵ㡣
		virtual void render();
		// ������ɫ���͵�ǰ�ڵ��ģ�;��󣬵��õ�����
		virtual void renderHeader();
		// �ݹ���Ⱦ���ӽڵ�
		virtual void renderChildren();
		// ÿ֡һ�εĵ�����,dtΪ��֡����һ֮֡���ʱ����(��λ����)
		virtual void update(float dt) {}
	protected:
		// ����ʹ�ô˷�����
		// �˷���ֻ��Ӱ�쵽���ڵ���ӽڵ㼯�ϣ��������޸��ӽڵ�ĸ��ڵ����ԡ�
		// Ҫ���������ڵ㣬����ӽڵ�ʹ��setParent������
		void addChild(Node* c);
		Node* parent;
	private:
		// �ӽڵ㼯��
		std::list<Node*> children;
		// ��һ֡ʱ�䡣������¼��֮֡���ʱ����
		float lastTime;
	};
}
