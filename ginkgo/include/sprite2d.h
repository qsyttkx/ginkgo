#pragma once

#include <macros.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <node.h>
#include <texture.h>

namespace ginkgo
{
	
	class DLL Sprite2D :public Node
	{
	public:
		Sprite2D(Node* parent, Texture img);
		virtual ~Sprite2D();
		virtual void render();
	private:
		Texture img;
		GLuint VAO, VBO;
	};
}