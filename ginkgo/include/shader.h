#pragma once

#include <macros.h>
#include <string>
#include <glm/glm.hpp>

namespace ginkgo
{
    /// <summary>��ɫ��</summary>
    class DLL Shader
    {
    public:
        /// <summary>ʵ�����ڽ���ɫ��</summary>
        /// <param name="name">�ڽ���ɫ��������</param>
        Shader(std::string name);
        /// <param name="vsPath">������ɫ�����ļ���·��</param>
        /// <param name="fsPath">Ƭ����ɫ�����ļ���·��</param>
        Shader(const char* vsPath, const char* fsPath);
        /// <summary>ʹ�ø���ɫ��</summary>
        void use();
        /// <summary>��GPU�ͷŸ���ɫ������Դ</summary>
        void release();
        /// <summary>����bool��(��ʵ��int)uniform</summary>
        /// <param name="name">uniform��</param>
        /// <param name="value">uniformֵ</param>
        void setBool(const char* name, bool value) const;
        /// <summary>����int��uniform</summary>
        /// <param name="name">uniform��</param>
        /// <param name="value">uniformֵ</param>
        void setInt(const char* name, int value) const;
        /// <summary>����float��uniform</summary>
        /// <param name="name">uniform��</param>
        /// <param name="value">uniformֵ</param>
        void setFloat(const char* name, float value) const;
        /// <summary>����Mat4��uniform</summary>
        /// <param name="name">uniform��</param>
        /// <param name="value">uniformֵ</param>
        void setMat4(const char* name, glm::mat4 matrix) const;
        /// <summary>����vec2��uniform</summary>
        /// <param name="name">uniform��</param>
        /// <param name="value">uniformֵ</param>
        void setVec2(const char* name, glm::vec2 value) const;
        /// <summary>����vec3��uniform</summary>
        /// <param name="name">uniform��</param>
        /// <param name="value">uniformֵ</param>
        void setVec3(const char* name, glm::vec3 value) const;
        /// <summary>����vec4��uniform</summary>
        /// <param name="name">uniform��</param>
        /// <param name="value">uniformֵ</param>
        void setVec4(const char* name, glm::vec4 value) const;
        /// <summary>��ȡ��ɫ����ID</summary>
        unsigned int getID();
        /// ������һЩ�ڽ��Ļ�����ɫ��
        /// <summary>������ɫ����ֻ��һ��������ͼ��û�й���</summary>
        static Shader basicDiffuse;
    private:
        /// <summary>��ɫ��������opengl�е�id</summary>
        unsigned int id;
        /// <summary>��ȡ�����ļ�����</summary>
        std::string readCode(const char* path);
        /// <summary>������ɫ��</summary>
        unsigned int compileShader(const char* code, unsigned int shaderType);
    };

    /// basicDiffuse
    const char vs_basicDiffuse[] =
        "#version 330 core\n"
        "layout(location = 0) in vec3 aPos;\n"
        "layout(location = 1) in vec2 aTexCoords;\n"
        "out vec2 TexCoords;\n"
        "// ģ����ͼͶӰ����\n"
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
        "// ����һ����������ͼ\n"
        "uniform sampler2D texture_diffuse1;\n"
        "void main()\n"
        "{\n"
        "    FragColor = texture(texture_diffuse1, TexCoords);\n"
        "    //FragColor = vec4(1,0,0,1);\n"
        "}";
}