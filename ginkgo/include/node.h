#pragma once

#include <list>
#include <string>
#include <glm/glm.hpp>
#include <macros.h>
#include <shader.h>

namespace ginkgo
{
	// 节点对象
	class DLL Node
	{
	public:
		//Node();
		Node(Node* parent = NULL);
		~Node();
		// 设置父节点
		void setParent(Node* p);
		// 获取父节点
		Node* getParent();
		// 获取子节点集合
		std::list<Node*> getChildren();
		// 移除指定子节点
		void removeChild(Node* n, bool releaseChildren = false);
		// 移除所有子节点
		void removeAllChildren(bool releaseChildren = false);
		// 从父节点中移除本节点
		void removedFromParent();
		// 节点名字
		std::string name;
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scaling;
		glm::mat4 getTransform();
		glm::vec3 globalPosition();
		glm::vec3 globalRotation();
		glm::vec3 globalScaling();
		glm::mat4 getGlobalTransform();
		// 渲染改节点
		// 在重写的render方法中，需要在开头调用renderHeader()以设置着色器和当前节点的模型矩阵，
		// 而在结尾部分需要调用renderChildren()方法以递归渲染其子节点。
		virtual void render();
		// 设置着色器和当前节点的模型矩阵，调用调度器
		virtual void renderHeader();
		// 递归渲染其子节点
		virtual void renderChildren();
		// 每帧一次的调度器,dt为此帧与上一帧之间的时间间隔(单位：秒)
		virtual void update(float dt) {}
	protected:
		// 请勿使用此方法！
		// 此方法只会影响到本节点的子节点集合，而不会修改子节点的父节点属性。
		// 要连接两个节点，请对子节点使用setParent方法。
		void addChild(Node* c);
		Node* parent;
	private:
		// 子节点集合
		std::list<Node*> children;
		// 上一帧时间。用来记录两帧之间的时间间隔
		float lastTime;
	};
}
