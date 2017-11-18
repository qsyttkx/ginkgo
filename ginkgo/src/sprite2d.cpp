#include <sprite2d.h>

using namespace ginkgo;
using namespace glm;

Sprite2D::Sprite2D(Texture img, Node* p) :Node(p)
{
	this->img = img;
	vec2 halfsize(img.width*0.5f, img.height*0.5f);
	float vertices[] =
	{	// 这样设置顶点位置可以使得锚点在图片中心
		// 顶点位置						   纹理坐标
		-halfsize.x,  halfsize.y, 0.0f,    0.0f, 1.0f,
		-halfsize.x, -halfsize.y, 0.0f,    0.0f, 0.0f,
		halfsize.x, -halfsize.y,  0.0f,    1.0f, 0.0f,
									      
		-halfsize.x,  halfsize.y, 0.0f,    0.0f, 1.0f,
		halfsize.x, -halfsize.y,  0.0f,    1.0f, 0.0f,
		halfsize.x,  halfsize.y,  0.0f,    1.0f, 1.0f
	};

	// 生成VAO, VBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
	glBindVertexArray(0);
}

void Sprite2D::render()
{
	renderHeader();

	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, img.id);
	Shader::basicDiffuse.setInt("texture_diffuse1", 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	renderChildren();
}