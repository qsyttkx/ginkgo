#define EXPORT
#include <macros.h>
#include <texture.h>
#include <iostream>

using namespace ginkgo;
using namespace std;

Texture::Texture()
{
	// 啥也不做的空贴图
	id = 0;
}

Texture::Texture(std::string path)
{
    glGenTextures(1, &id);
    // 由于OpenGL读取纹理的方向不一样我们需要在加载时反转所有纹理
    stbi_set_flip_vertically_on_load(true);

    int nrComponents;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        if (nrComponents == 1)format = GL_RED;
        else if (nrComponents == 3)format = GL_RGB;
        else if (nrComponents == 4)format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        //glGenerateMipmap(GL_TEXTURE_2D);//生成mipmap

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "加载纹理失败(" << path << ")" << std::endl;
    }
}

// 用颜色生成一张贴图，颜色分量是float型的
Texture::Texture(glm::vec4 color)
{
    glGenTextures(1, &id);
    width = height = 1;
    format = GL_RGBA;
    unsigned char data[4];
	data[0] = (unsigned char)(255 * color.r);
	data[1] = (unsigned char)(255 * color.g);
	data[2] = (unsigned char)(255 * color.b);
	data[3] = (unsigned char)(255 * color.a);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void Texture::release()
{
	if (id)
	{
		glDeleteTextures(1, &id);
	}
	cout << "Texture[" << id << "] has been released." << endl;
}