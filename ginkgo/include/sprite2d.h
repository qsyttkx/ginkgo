#pragma once

#include <macros.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <node.h>
#include <texture.h>
#include <animation.h>

namespace ginkgo
{
    /// <summary>2D精灵，继承自Node，其实就是矩形的模型而已</summary>
	class DLL Sprite2D :public Node
	{
	public:
        /// <summary>构建一个2D精灵</summary>
        /// <param name="parent">父节点</param>
        /// <param name="img">纹理</param>
		Sprite2D(Node* parent, Texture img);
        /// <summary>析构</summary>
		virtual ~Sprite2D();
        /// <summary>渲染</summary>
		virtual void render();
        /// <summary>当前纹理ID（可能会被animator替换）</summary>
        GLuint textureID;
	private:
        /// <summary>纹理</summary>
		Texture img;
        /// <summary>顶点数组、缓冲对象</summary>
		GLuint VAO, VBO;
	};
}