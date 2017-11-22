#pragma once

#include <macros.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <node.h>
#include <texture.h>
#include <animation.h>

namespace ginkgo
{
    /// <summary>2D���飬�̳���Node����ʵ���Ǿ��ε�ģ�Ͷ���</summary>
	class DLL Sprite2D :public Node
	{
	public:
        /// <summary>����һ��2D����</summary>
        /// <param name="parent">���ڵ�</param>
        /// <param name="img">����</param>
		Sprite2D(Node* parent, Texture img);
        /// <summary>����</summary>
		virtual ~Sprite2D();
        /// <summary>��Ⱦ</summary>
		virtual void render();
        /// <summary>��ǰ����ID�����ܻᱻanimator�滻��</summary>
        GLuint textureID;
	private:
        /// <summary>����</summary>
		Texture img;
        /// <summary>�������顢�������</summary>
		GLuint VAO, VBO;
	};
}