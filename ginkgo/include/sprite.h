#pragma once

#include <macros.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <node.h>
#include <texture.h>

namespace ginkgo
{
    //2D精灵，继承自Node，其实就是矩形的模型而已
	class DLL Sprite :public Node
	{
	public:
        //构建一个不带纹理的2D精灵
        Sprite(Node* parent);
        //构建一个2D精灵
        //父节点
        //纹理
        Sprite(Node* parent, Texture img);

        void setTexture(Texture img);
        //析构
		virtual ~Sprite();
        //调度器
        virtual void update(float dt);
        //是否正在播放动画
        bool isPlayingAnimation;
	private:
        bool hasTexture;

        //纹理
		Texture img;
        //顶点数组、缓冲对象
		GLuint VAO, VBO;
	};
}