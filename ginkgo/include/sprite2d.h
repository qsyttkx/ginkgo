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
		Sprite2D(Texture img, Node* parent = NULL);
		virtual void render();
	private:
		Texture img;
		GLuint VAO, VBO;
	};
}