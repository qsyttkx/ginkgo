#pragma once

#include <macros.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <node.h>
#include <texture.h>

namespace ginkgo
{
    /// <summary>2D精灵，继承自Node，其实就是矩形的模型而已</summary>
	class DLL Sprite :public Node
	{
	public:
        /// <summary>构建一个不带纹理的2D精灵</summary>
        Sprite(Node* parent);
        /// <summary>构建一个2D精灵</summary>
        /// <param name="parent">父节点</param>
        /// <param name="img">纹理</param>
        Sprite(Node* parent, Texture img);

        void setTexture(Texture img);
        /// <summary>析构</summary>
		virtual ~Sprite();
        /// <summary>调度器</summary>
        virtual void update(float dt);
        /// <summary>是否正在播放动画</summary>
        bool isPlayingAnimation;
	private:
        bool hasTexture;

        /// <summary>纹理</summary>
		Texture img;
        /// <summary>顶点数组、缓冲对象</summary>
		GLuint VAO, VBO;
	};
}