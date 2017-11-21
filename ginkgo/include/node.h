#pragma once

#include <macros.h>
#include <list>
#include <string>
#include <glm/glm.hpp>
#include <shader.h>

namespace ginkgo
{
	// 节点对象
	class DLL Node
	{
	public:
        /// <summary>构造函数</summary>
        /// <param name="parent">此节点的父节点，若为</param>
		Node(Node* parent = NULL);
		virtual ~Node();
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
        //这个貌似有点问题，先禁用了。。。你说如果我在父节点先旋转了个45度，然后再把它y方向伸缩为0.5，那它就是斜着扁的啊，这个怎么用scaling表示。。。
		//glm::vec3 globalScaling();
		glm::mat4 getGlobalTransform();
		// 渲染改节点
		// 在重写的render方法中，需要在开头调用renderHeader()以设置着色器和当前节点的模型矩阵，
		// 而在结尾部分需要调用renderChildren()方法以递归渲染其子节点。
		virtual void render();
		// 设置着色器和当前节点的模型矩阵，调用调度器，刷新transform
		virtual void renderHeader();
		// 递归渲染其子节点
		virtual void renderChildren();
		// 每帧一次的调度器,dt为此帧与上一帧之间的时间间隔(单位：秒)
		virtual void update(float dt) {}
		// 是否应当手动排序，默认为否。
		// 当为是时，在渲染该节点之前会将其与兄弟节点按离视角位置远近进行排序，越远的越先渲染。
		// 如果这个节点具有透明的贴图时我们会期望使用手动排序，否则由于深度测试的原因可能会丢弃
		// 一些片段。
		bool shouldSort;
		// 重写的小于运算符
		bool operator<(const Node& n) const;
	protected:
		// 请勿使用此方法！
		// 此方法只会影响到本节点的子节点集合，而不会修改子节点的父节点属性。
		// 要连接两个节点，请对子节点使用setParent方法。
		void addChild(Node* c);
		Node* parent;
	private:
        glm::mat4 transform;
        glm::mat4 parentsGlobalTransform;
        glm::mat4 globalTransform;
		// 子节点集合
		std::list<Node*> children;
		// 上一帧时间。用来记录两帧之间的时间间隔
		float lastTime;
		// 获取摄像机位置，用于计算渲染顺序。对于纹理是透明的物体，由于深度测试的影响可能会出现问题
		glm::vec3 getPositionOfRootCamera() const;
	};
}
