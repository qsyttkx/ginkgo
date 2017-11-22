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
        /// <summary>贴图在OpenGL中的ID</summary>
        GLuint id;
        /// <summary>贴图类型（漫反射啊镜面反射啊啥的）</summary>
        std::string type;
        /// <summary>贴图文件路径（可以用来对比是不是重复加载了贴图）</summary>
        std::string path;
        /// <summary>尺寸</summary>
        int width, height;
        /// <summary>格式</summary>
        GLenum format;
        /// <summary>空的贴图</summary>
		Texture();
        /// <summary>加载一张贴图</summary>
        /// <param name="path">图片资源路径</param>
        Texture(std::string path);
        /// <summary>用颜色生成一张贴图，颜色分量是float型的</summary>
        /// <param name="color">颜色值，如红色vec4(1.0f,0.0f,0.0f,1.0f)</param>
        Texture(glm::vec4 color);
        /// <summary>从GPU中释放贴图资源</summary>
		void release();
    };
}