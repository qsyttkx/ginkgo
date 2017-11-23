#pragma once

#include <macros.h>
#include <string>
#include <glm/glm.hpp>

namespace ginkgo
{
    /// <summary>着色器</summary>
    class DLL Shader
    {
    public:
		/// <summary>空的着色器，由于几个内建的着色器是静态变量，但是编译需要等到初始化完毕所以先调用这个空的构建函数</summary>
		Shader() {}
		/// <summary>实例化内建着色器</summary>
        /// <param name="vsPath">顶点着色程序文件的路径</param>
        /// <param name="fsPath">片段着色程序文件的路径</param>
        Shader(const char* vsPath, const char* fsPath);
        /// <summary>使用该着色器</summary>
        void use();
        /// <summary>从GPU释放该着色器的资源</summary>
        void release();
        /// <summary>设置bool型(其实是int)uniform</summary>
        /// <param name="name">uniform名</param>
        /// <param name="value">uniform值</param>
        void setBool(const char* name, bool value) const;
        /// <summary>设置int型uniform</summary>
        /// <param name="name">uniform名</param>
        /// <param name="value">uniform值</param>
        void setInt(const char* name, int value) const;
        /// <summary>设置float型uniform</summary>
        /// <param name="name">uniform名</param>
        /// <param name="value">uniform值</param>
        void setFloat(const char* name, float value) const;
        /// <summary>设置Mat4型uniform</summary>
        /// <param name="name">uniform名</param>
        /// <param name="value">uniform值</param>
        void setMat4(const char* name, glm::mat4 matrix) const;
        /// <summary>设置vec2型uniform</summary>
        /// <param name="name">uniform名</param>
        /// <param name="value">uniform值</param>
        void setVec2(const char* name, glm::vec2 value) const;
        /// <summary>设置vec3型uniform</summary>
        /// <param name="name">uniform名</param>
        /// <param name="value">uniform值</param>
        void setVec3(const char* name, glm::vec3 value) const;
        /// <summary>设置vec4型uniform</summary>
        /// <param name="name">uniform名</param>
        /// <param name="value">uniform值</param>
        void setVec4(const char* name, glm::vec4 value) const;
        /// <summary>获取着色器的ID</summary>
        unsigned int getID();
		/// <summary>编译内建着色器</summary>
		static void buildBuiltinShaders();
        /// 以下是一些内建的基本着色器
        /// <summary>基础着色器，只有一个纹理贴图，没有光照</summary>
        static Shader basicDiffuse;
    private:
		/// <summary>实例化内建着色器</summary>
		/// <param name="name">内建着色器的名字</param>
		Shader(std::string name);
        /// <summary>着色器程序在opengl中的id</summary>
        unsigned int id;
        /// <summary>读取代码文件内容</summary>
        std::string readCode(const char* path);
        /// <summary>编译着色器</summary>
        unsigned int compileShader(const char* code, unsigned int shaderType);
    };

    /// basicDiffuse
    const char vs_basicDiffuse[] =
        "#version 330 core\n"
        "layout(location = 0) in vec3 aPos;\n"
        "layout(location = 1) in vec2 aTexCoords;\n"
        "out vec2 TexCoords;\n"
        "// 模型视图投影矩阵\n"
        "uniform mat4 model;\n"
        "uniform mat4 view;\n"
        "uniform mat4 projection;\n"
        "void main()\n"
        "{\n"
        "TexCoords = aTexCoords;\n"
        "	gl_Position = projection*view*model*vec4(aPos, 1.0);\n"
        "}";
    const char fs_basicDiffuse[] =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in  vec2 TexCoords;\n"
        "uniform float node_opacity;\n"
        "// 接受一个漫反射贴图\n"
        "uniform sampler2D texture_diffuse1;\n"
        "void main()\n"
        "{\n"
		"    FragColor = texture(texture_diffuse1, TexCoords)*vec4(1,1,1,node_opacity);\n"
        "    //FragColor = vec4(1,0,0,1);\n"
        "}";
}