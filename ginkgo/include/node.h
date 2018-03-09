#pragma once

#include <macros.h>
#include <list>
#include <string>
#include <glm/glm.hpp>
#include <shader.h>

namespace ginkgo
{
    //节点
    //我们游戏中的许多对象都继承自Node类。它可以实现一个树形结构，便于我们进行组织场景和进行变换。
    /// 它还可以半自动地管理内存，当一个节点被释放时，其子树节点也会全部被释放
    /// （不过对于本节点中没有加入子树的对象仍需要手动管理）
	class DLL Node
	{
	public:
        //构造函数
        //此节点的父节点，若为空则表明这是一个根节点，不会被自动释放
		Node(Node* parent = NULL);
        //析构函数
		virtual ~Node();
        //设置父节点
        //此节点的父节点
		void setParent(Node* p);
        //获取父节点
		//返回Node*，为其父节点
		Node* getParent();
        //获取子节点集合
        //返回值为一个list，包含其子节点
		std::list<Node*> getChildren();
        //移除指定子节点
        //将要被移除的节点的指针
        //是否要释放掉这个节点的内存，默认是不释放
		void removeChild(Node* n, bool release = false);
        //移除所有子节点
        //是否要释放掉所有子节点的内存，默认是不释放
		void removeAllChildren(bool releaseChildren = false);
        //从父节点中移除本节点，这个操作不会释放本节点的内存
		void removedFromParent();
		//节点名字
		std::string name;
		//节点是启用，默认为是
		bool isEnabled;
		//是否应当手动排序，默认为是。
		/// 当为是时，在渲染该节点之前会将其与兄弟节点按离视角位置远近进行排序，越远的越先渲染。
		/// 如果这个节点具有透明的贴图时我们会期望使用手动排序，否则由于深度测试的原因可能会丢弃
		/// 一些片段。但是这样会一定程度上影响性能。
		bool shouldSort;
		//节点的透明度，默认为1.0f不透明
		float opacity;
        //位置属性（局部坐标系）
		glm::vec3 position;
        //旋转属性（欧拉角表示，XYZ顺序，局部坐标系）
		glm::vec3 rotation;
        //缩放属性（局部坐标系）
		glm::vec3 scaling;
		//获取合成的opacity
		float getGlobalOpacity();
		//获取变换矩阵（局部坐标系）
		glm::mat4 getTransform();
        //获取位置（世界坐标系）
		glm::vec3 globalPosition() const;
        /// 这几个貌似有点问题我还没想好，所以先禁了。。。
        /// 获取旋转欧拉角
		/// glm::vec3 globalRotation();
        /// 你说如果我在父节点先旋转了个45度，然后再把它y方向伸缩为0.5，那它就是斜着扁的啊，这个怎么用scaling表示。。。
		/// glm::vec3 globalScaling();

        //获取变换矩阵（世界坐标系）
        virtual glm::mat4 getGlobalTransform();
        //渲染前的一些操作，如传递当前节点的模型矩阵，调用调度器，刷新transform等
        /// 在重写的Node类中，如果实例化出的节点是一个根节点，则需要手动在render()之前调用renderHeader()
        /// 以设置着色器和当前节点的模型矩阵
		virtual void renderHeader();
        //递归渲染其子节点
		virtual void renderChildren();
        //逐帧调度器，可以在这个函数中实现许多的功能
        //为此帧与上一帧之间的时间间隔(单位：秒)
        virtual void update(float dt);
        //重写的小于运算符
		bool operator<(const Node& n) const;
        // 着色器程序，NULL则使用默认着色器
        Shader* shader;
        void setBlendFunc(unsigned int func1, unsigned int func2);
	protected:
		//请勿使用此方法！
		// 此方法只会影响到本节点的子节点集合，而不会修改子节点的父节点属性。
		// 要连接两个节点，请对子节点使用setParent方法。
		void addChild(Node* c);
        //父节点
		Node* parent;
        //两帧之间隔
        float dt;
		//父级opacity
		float parentsOpacity;
		//最终合成的opacity
		float globalOpacity;
        //变换矩阵
        glm::mat4 transform;
        //父节点的全局变换矩阵(相对世界坐标系而言这个节点所在的坐标系)
        glm::mat4 parentsGlobalTransform;
        //全局变换矩阵
        glm::mat4 globalTransform;
        //子节点list
		std::list<Node*> children;
        //获取摄像机位置，用于计算渲染顺序。
		glm::vec3 getPositionOfRootCamera() const;
        unsigned int blendfunc1, blendfunc2;
	};
}
