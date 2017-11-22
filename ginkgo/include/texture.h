#pragma once

#include <macros.h>
#include <string>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <stb_image.h>
#include <node.h>

namespace ginkgo
{
    struct DLL Texture
    {
        /// <summary>��ͼ��OpenGL�е�ID</summary>
        GLuint id;
        /// <summary>��ͼ���ͣ������䰡���淴�䰡ɶ�ģ�</summary>
        std::string type;
        /// <summary>��ͼ�ļ�·�������������Ա��ǲ����ظ���������ͼ��</summary>
        std::string path;
        /// <summary>�ߴ�</summary>
        int width, height;
        /// <summary>��ʽ</summary>
        GLenum format;
        /// <summary>�յ���ͼ</summary>
		Texture();
        /// <summary>����һ����ͼ</summary>
        /// <param name="path">ͼƬ��Դ·��</param>
        Texture(std::string path);
        /// <summary>����ɫ����һ����ͼ����ɫ������float�͵�</summary>
        /// <param name="color">��ɫֵ�����ɫvec4(1.0f,0.0f,0.0f,1.0f)</param>
        Texture(glm::vec4 color);
        /// <summary>��GPU���ͷ���ͼ��Դ</summary>
		void release();
    };
}