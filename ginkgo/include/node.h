#pragma once

#include <macros.h>
#include <list>
#include <string>
#include <glm/glm.hpp>
#include <shader.h>

namespace ginkgo
{
    /// <summary>节点</summary>
    /// <para>我们游戏中的许多对象都继承自Node类。它可以实现一个树形结构，便于我们进行组织场景和进行变换。
    /// 它还可以半自动地管理内存，当一个节点被释放时，其子树节点也会全部被释放
    /// （不过对于本节点中没有加入子树的对象仍需要手动管理）</para>
	class DLL Node
	{
	public:
        /// <summary>构造函数</summary>
        /// <param name="parent">此节点的父节点，若为空则表明这是一个根节点，不会被自动释放</param>
		Node(Node* parent = NULL);
        /// <summary>析构函数</summary>
		virtual ~Node();
        /// <summary>设置父节点</summary>
        /// <param name="p">此节点的父节点</param>
		void setParent(Node* p);
        /// <summary>获取父节点</summary>
		/// <returns>返回Node*，为其父节点</returns>
		Node* getParent();
        /// <summary>获取子节点集合</summary>
        /// <returns>返回值为一个list，包含其子节点</returns>
		std::list<Node*> getChildren();
        /// <summary>移除指定子节点</summary>
        /// <param name="n">将要被移除的节点的指针</param>
        /// <param name="release">是否要释放掉这个节点的内存，默认是不释放</param>
		void removeChild(Node* n, bool release = false);
        /// <summary>移除所有子节点</summary>
        /// <param name="releaseChildren">是否要释放掉所有子节点的内存，默认是不释放</param>
		void removeAllChildren(bool releaseChildren = false);
        /// <summary>从父节点中移除本节点，这个操作不会释放本节点的内存</summary>
		void removedFromParent();
        /// <summary>节点名字</summary>
		std::string name;
        /// <summary>位置属性（局部坐标系）</summary>
		glm::vec3 position;
        /// <summary>旋转属性（欧拉角表示，XYZ顺序，局部坐标系）</summary>
		glm::vec3 rotation;
        /// <summary>缩放属性（局部坐标系）</summary>
		glm::vec3 scaling;
        /// <summary>获取变换矩阵（局部坐标系）</summary>
		glm::mat4 getTransform();
        /// <summary>获取位置（世界坐标系）</summary>
		glm::vec3 globalPosition();
        /// 这几个貌似有点问题我还没想好，所以先禁了。。。
        /// 获取旋转欧拉角
		/// glm::vec3 globalRotation();
        /// 你说如果我在父节点先旋转了个45度，然后再把它y方向伸缩为0.5，那它就是斜着扁的啊，这个怎么用scaling表示。。。
		/// glm::vec3 globalScaling();

        /// <summary>获取变换矩阵（世界坐标系）</summary>
        glm::mat4 getGlobalTransform();
		/// <summary>渲染该节点，该方法会递归调用以渲染其下所有节点。着色器为默认的基本着色器（只直接渲染一个纹理）</summary>
		virtual void render();
        /// <summary>渲染前的一些操作，如传递当前节点的模型矩阵，调用调度器，刷新transform等
        /// 在重写的Node类中，如果实例化出的节点是一个根节点，则需要手动在render()之前调用renderHeader()
        /// 以设置着色器和当前节点的模型矩阵</summary>
		virtual void renderHeader();
        /// <summary>递归渲染其子节点</summary>
		virtual void renderChildren();
        /// <summary>逐帧调度器，可以在这个函数中实现许多的功能</summary>
        /// <param name="dt">为此帧与上一帧之间的时间间隔(单位：秒)</param>
		virtual void update(float dt) {}
        /// <summary>是否应当手动排序，默认为否。
		/// 当为是时，在渲染该节点之前会将其与兄弟节点按离视角位置远近进行排序，越远的越先渲染。
		/// 如果这个节点具有透明的贴图时我们会期望使用手动排序，否则由于深度测试的原因可能会丢弃
		/// 一些片段。</summary>
		bool shouldSort;
        /// <summary>重写的小于运算符</summary>
		bool operator<(const Node& n) const;
	protected:
		/// <summary>请勿使用此方法！
		/// 此方法只会影响到本节点的子节点集合，而不会修改子节点的父节点属性。
		/// 要连接两个节点，请对子节点使用setParent方法。</summary>
		void addChild(Node* c);
        /// <summary>父节点</summary>
		Node* parent;
	private:
        /// <summary>变换矩阵</summary>
        glm::mat4 transform;
        /// <summary>父节点的全局变换矩阵(相对世界坐标系而言这个节点所在的坐标系)</summary>
        glm::mat4 parentsGlobalTransform;
        /// <summary>全局变换矩阵</summary>
        glm::mat4 globalTransform;
        /// <summary>子节点list</summary>
		std::list<Node*> children;
        /// <summary>上一帧时间，用来计算两帧之间的时间间隔。</summary>
		float lastTime;
        /// <summary>获取摄像机位置，用于计算渲染顺序。</summary>
		glm::vec3 getPositionOfRootCamera() const;
	};
}
