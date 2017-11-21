#pragma once

#include <macros.h>
#include <list>
#include <string>
#include <glm/glm.hpp>
#include <shader.h>

namespace ginkgo
{
	// �ڵ����
	class DLL Node
	{
	public:
        /// <summary>���캯��</summary>
        /// <param name="parent">�˽ڵ�ĸ��ڵ㣬��Ϊ</param>
		Node(Node* parent = NULL);
		virtual ~Node();
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
        //���ò���е����⣬�Ƚ����ˡ�������˵������ڸ��ڵ�����ת�˸�45�ȣ�Ȼ���ٰ���y��������Ϊ0.5����������б�ű�İ��������ô��scaling��ʾ������
		//glm::vec3 globalScaling();
		glm::mat4 getGlobalTransform();
		// ��Ⱦ�Ľڵ�
		// ����д��render�����У���Ҫ�ڿ�ͷ����renderHeader()��������ɫ���͵�ǰ�ڵ��ģ�;���
		// ���ڽ�β������Ҫ����renderChildren()�����Եݹ���Ⱦ���ӽڵ㡣
		virtual void render();
		// ������ɫ���͵�ǰ�ڵ��ģ�;��󣬵��õ�������ˢ��transform
		virtual void renderHeader();
		// �ݹ���Ⱦ���ӽڵ�
		virtual void renderChildren();
		// ÿ֡һ�εĵ�����,dtΪ��֡����һ֮֡���ʱ����(��λ����)
		virtual void update(float dt) {}
		// �Ƿ�Ӧ���ֶ�����Ĭ��Ϊ��
		// ��Ϊ��ʱ������Ⱦ�ýڵ�֮ǰ�Ὣ�����ֵܽڵ㰴���ӽ�λ��Զ����������ԽԶ��Խ����Ⱦ��
		// �������ڵ����͸������ͼʱ���ǻ�����ʹ���ֶ����򣬷���������Ȳ��Ե�ԭ����ܻᶪ��
		// һЩƬ�Ρ�
		bool shouldSort;
		// ��д��С�������
		bool operator<(const Node& n) const;
	protected:
		// ����ʹ�ô˷�����
		// �˷���ֻ��Ӱ�쵽���ڵ���ӽڵ㼯�ϣ��������޸��ӽڵ�ĸ��ڵ����ԡ�
		// Ҫ���������ڵ㣬����ӽڵ�ʹ��setParent������
		void addChild(Node* c);
		Node* parent;
	private:
        glm::mat4 transform;
        glm::mat4 parentsGlobalTransform;
        glm::mat4 globalTransform;
		// �ӽڵ㼯��
		std::list<Node*> children;
		// ��һ֡ʱ�䡣������¼��֮֡���ʱ����
		float lastTime;
		// ��ȡ�����λ�ã����ڼ�����Ⱦ˳�򡣶���������͸�������壬������Ȳ��Ե�Ӱ����ܻ��������
		glm::vec3 getPositionOfRootCamera() const;
	};
}
