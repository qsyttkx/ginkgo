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
        //贴图在OpenGL中的ID
        GLuint id;
        //贴图类型（漫反射啊镜面反射啊啥的）
        std::string type;
        //贴图文件路径（可以用来对比是不是重复加载了贴图）
        std::string path;
        //尺寸
        int width, height;
        //格式
        GLenum format;
        //空的贴图
		Texture();
        //加载一张贴图
        //图片资源路径
        Texture(std::string path);
        //用颜色生成一张贴图，颜色分量是float型的
        //颜色值，如红色vec4(1.0f,0.0f,0.0f,1.0f)
        Texture(glm::vec4 color);
        //从GPU中释放贴图资源
		void release();
    };
}