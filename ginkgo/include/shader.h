#pragma once

#include <macros.h>
#include <string>
#include <glm/glm.hpp>

namespace ginkgo
{
    class DLL Shader
    {
    public:
        // 空的着色器
        // 请不要使用这个构造函数
        Shader() {}
        //着色器构造函数
        Shader(const char* vsPath, const char* fsPath);
        ~Shader();

        //使用该着色器
        void use();

        //设置boolean型Uniform值
        void setBool(const char* name, bool value) const;
        //设置int型Uniform值
        void setInt(const char* name, int value) const;
        //设置float型Uniform值
        void setFloat(const char* name, float value) const;
        //设置Mat4型Uniform值
        void setMat4(const char* name, glm::mat4 matrix) const;
        //设置Vec2型Uniform值
        void setVec2(const char* name, glm::vec2 value) const;
        //设置Vec3型Uniform值
        void setVec3(const char* name, glm::vec3 value) const;
        //设置Vec4型Uniform值
        void setVec4(const char* name, glm::vec4 value) const;
        //获取着色器的ID
        unsigned int getID();

        // 构建内建的基础着色器
        static void buildBuiltinShaders();
        // 以下是一些内建的基本着色器
        static Shader basicDiffuse;
    private:
        // 着色器程序在opengl中的id
        unsigned int id;
        // 读取代码文件内容
        std::string readCode(const char* path);
        // 编译着色器
        unsigned int compileShader(const char* code, unsigned int shaderType);
        // 实例化内建着色器
        Shader(std::string type);
    };

    const char vs_basicDiffuse[] =
        "#version 330 core\n\
        layout(location = 0) in vec3 aPos;\n\
        layout(location = 1) in vec2 aTexCoords;\n\
        out vec2 TexCoords;\n\
        // 模型视图投影矩阵\n\
        uniform mat4 model;\n\
        uniform mat4 view;\n\
        uniform mat4 projection;\n\
        void main()\n\
        {\n\
        TexCoords = aTexCoords;\n\
        	gl_Position = projection*view*model*vec4(aPos, 1.0);\n\
        }";
    const char fs_basicDiffuse[] =
        "#version 330 core\n\
        out vec4 FragColor;\n\
		in  vec2 TexCoords;\n\
		// 接受一个漫反射贴图\n\
		uniform sampler2D texture_diffuse1;\n\
		void main()\n\
		{\n\
		    FragColor = texture(texture_diffuse1, TexCoords);\n\
		    //FragColor = vec4(1,0,0,1);\n\
		}";
}