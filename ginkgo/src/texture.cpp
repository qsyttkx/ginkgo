#define EXPORT
#include <macros.h>
#include <texture.h>
#include <iostream>

using namespace ginkgo;
using namespace std;

Texture::Texture()
{
	// ɶҲ�����Ŀ���ͼ
	id = 0;
}

Texture::Texture(std::string path)
{
    glGenTextures(1, &id);
    // ����OpenGL��ȡ����ķ���һ��������Ҫ�ڼ���ʱ��ת��������
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
        glGenerateMipmap(GL_TEXTURE_2D);//����mipmap

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "��������ʧ��(" << path << ")" << std::endl;
    }
}

// ����ɫ����һ����ͼ����ɫ������float�͵�
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