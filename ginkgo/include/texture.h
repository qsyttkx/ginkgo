#pragma once

#include <string>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stb_image.h>
#include <macros.h>

namespace ginkgo
{
    struct DLL Texture
    {
        // ��ͼ��OpenGL�е�ID
        GLuint id;
        // ��ͼ���ͣ������䰡���淴�䰡ɶ�ģ�
        std::string type;
        // ��ͼ�ļ�·�������������Ա��ǲ����ظ���������ͼ��
        std::string path;
        // �ߴ�
        int width, height;
        // ��ʽ
        GLenum format;
        Texture() {}// �յ���ͼ
        // ����һ����ͼ
        Texture(std::string path);
        // ����ɫ����һ����ͼ����ɫ������float�͵�
        Texture(glm::vec3 color);
    };
}