#pragma once

#include <macros.h>
#include <list>
#include <string>
#include <glm/glm.hpp>
#include <shader.h>

namespace ginkgo
{
    /// <summary>�ڵ�</summary>
    /// <para>������Ϸ�е������󶼼̳���Node�ࡣ������ʵ��һ�����νṹ���������ǽ�����֯�����ͽ��б任��
    /// �������԰��Զ��ع����ڴ棬��һ���ڵ㱻�ͷ�ʱ���������ڵ�Ҳ��ȫ�����ͷ�
    /// ���������ڱ��ڵ���û�м��������Ķ�������Ҫ�ֶ�����</para>
	class DLL Node
	{
	public:
        /// <summary>���캯��</summary>
        /// <param name="parent">�˽ڵ�ĸ��ڵ㣬��Ϊ�����������һ�����ڵ㣬���ᱻ�Զ��ͷ�</param>
		Node(Node* parent = NULL);
        /// <summary>��������</summary>
		virtual ~Node();
        /// <summary>���ø��ڵ�</summary>
        /// <param name="p">�˽ڵ�ĸ��ڵ�</param>
		void setParent(Node* p);
        /// <summary>��ȡ���ڵ�</summary>
		/// <returns>����Node*��Ϊ�丸�ڵ�</returns>
		Node* getParent();
        /// <summary>��ȡ�ӽڵ㼯��</summary>
        /// <returns>����ֵΪһ��list���������ӽڵ�</returns>
		std::list<Node*> getChildren();
        /// <summary>�Ƴ�ָ���ӽڵ�</summary>
        /// <param name="n">��Ҫ���Ƴ��Ľڵ��ָ��</param>
        /// <param name="release">�Ƿ�Ҫ�ͷŵ�����ڵ���ڴ棬Ĭ���ǲ��ͷ�</param>
		void removeChild(Node* n, bool release = false);
        /// <summary>�Ƴ������ӽڵ�</summary>
        /// <param name="releaseChildren">�Ƿ�Ҫ�ͷŵ������ӽڵ���ڴ棬Ĭ���ǲ��ͷ�</param>
		void removeAllChildren(bool releaseChildren = false);
        /// <summary>�Ӹ��ڵ����Ƴ����ڵ㣬������������ͷű��ڵ���ڴ�</summary>
		void removedFromParent();
        /// <summary>�ڵ�����</summary>
		std::string name;
        /// <summary>λ�����ԣ��ֲ�����ϵ��</summary>
		glm::vec3 position;
        /// <summary>��ת���ԣ�ŷ���Ǳ�ʾ��XYZ˳�򣬾ֲ�����ϵ��</summary>
		glm::vec3 rotation;
        /// <summary>�������ԣ��ֲ�����ϵ��</summary>
		glm::vec3 scaling;
        /// <summary>��ȡ�任���󣨾ֲ�����ϵ��</summary>
		glm::mat4 getTransform();
        /// <summary>��ȡλ�ã���������ϵ��</summary>
		glm::vec3 globalPosition();
        /// �⼸��ò���е������һ�û��ã������Ƚ��ˡ�����
        /// ��ȡ��תŷ����
		/// glm::vec3 globalRotation();
        /// ��˵������ڸ��ڵ�����ת�˸�45�ȣ�Ȼ���ٰ���y��������Ϊ0.5����������б�ű�İ��������ô��scaling��ʾ������
		/// glm::vec3 globalScaling();

        /// <summary>��ȡ�任������������ϵ��</summary>
        glm::mat4 getGlobalTransform();
		/// <summary>��Ⱦ�ýڵ㣬�÷�����ݹ��������Ⱦ�������нڵ㡣��ɫ��ΪĬ�ϵĻ�����ɫ����ֱֻ����Ⱦһ������</summary>
		virtual void render();
        /// <summary>��Ⱦǰ��һЩ�������紫�ݵ�ǰ�ڵ��ģ�;��󣬵��õ�������ˢ��transform��
        /// ����д��Node���У����ʵ�������Ľڵ���һ�����ڵ㣬����Ҫ�ֶ���render()֮ǰ����renderHeader()
        /// ��������ɫ���͵�ǰ�ڵ��ģ�;���</summary>
		virtual void renderHeader();
        /// <summary>�ݹ���Ⱦ���ӽڵ�</summary>
		virtual void renderChildren();
        /// <summary>��֡�����������������������ʵ�����Ĺ���</summary>
        /// <param name="dt">Ϊ��֡����һ֮֡���ʱ����(��λ����)</param>
		virtual void update(float dt) {}
        /// <summary>�Ƿ�Ӧ���ֶ�����Ĭ��Ϊ��
		/// ��Ϊ��ʱ������Ⱦ�ýڵ�֮ǰ�Ὣ�����ֵܽڵ㰴���ӽ�λ��Զ����������ԽԶ��Խ����Ⱦ��
		/// �������ڵ����͸������ͼʱ���ǻ�����ʹ���ֶ����򣬷���������Ȳ��Ե�ԭ����ܻᶪ��
		/// һЩƬ�Ρ�</summary>
		bool shouldSort;
        /// <summary>��д��С�������</summary>
		bool operator<(const Node& n) const;
	protected:
		/// <summary>����ʹ�ô˷�����
		/// �˷���ֻ��Ӱ�쵽���ڵ���ӽڵ㼯�ϣ��������޸��ӽڵ�ĸ��ڵ����ԡ�
		/// Ҫ���������ڵ㣬����ӽڵ�ʹ��setParent������</summary>
		void addChild(Node* c);
        /// <summary>���ڵ�</summary>
		Node* parent;
	private:
        /// <summary>�任����</summary>
        glm::mat4 transform;
        /// <summary>���ڵ��ȫ�ֱ任����(�����������ϵ��������ڵ����ڵ�����ϵ)</summary>
        glm::mat4 parentsGlobalTransform;
        /// <summary>ȫ�ֱ任����</summary>
        glm::mat4 globalTransform;
        /// <summary>�ӽڵ�list</summary>
		std::list<Node*> children;
        /// <summary>��һ֡ʱ�䣬����������֮֡���ʱ������</summary>
		float lastTime;
        /// <summary>��ȡ�����λ�ã����ڼ�����Ⱦ˳��</summary>
		glm::vec3 getPositionOfRootCamera() const;
	};
}
