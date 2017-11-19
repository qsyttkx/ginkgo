#pragma once

#include <macros.h>
#include <string>
#include <glm/glm.hpp>

namespace ginkgo
{
    class DLL Shader
    {
    public:
        // �յ���ɫ��
        // �벻Ҫʹ��������캯��
        Shader() {}
        //��ɫ�����캯��
        Shader(const char* vsPath, const char* fsPath);
        ~Shader();

        //ʹ�ø���ɫ��
        void use();

        //����boolean��Uniformֵ
        void setBool(const char* name, bool value) const;
        //����int��Uniformֵ
        void setInt(const char* name, int value) const;
        //����float��Uniformֵ
        void setFloat(const char* name, float value) const;
        //����Mat4��Uniformֵ
        void setMat4(const char* name, glm::mat4 matrix) const;
        //����Vec2��Uniformֵ
        void setVec2(const char* name, glm::vec2 value) const;
        //����Vec3��Uniformֵ
        void setVec3(const char* name, glm::vec3 value) const;
        //����Vec4��Uniformֵ
        void setVec4(const char* name, glm::vec4 value) const;
        //��ȡ��ɫ����ID
        unsigned int getID();

        // �����ڽ��Ļ�����ɫ��
        static void buildBuiltinShaders();
        // ������һЩ�ڽ��Ļ�����ɫ��
        static Shader basicDiffuse;
    private:
        // ��ɫ��������opengl�е�id
        unsigned int id;
        // ��ȡ�����ļ�����
        std::string readCode(const char* path);
        // ������ɫ��
        unsigned int compileShader(const char* code, unsigned int shaderType);
        // ʵ�����ڽ���ɫ��
        Shader(std::string type);
    };

    const char vs_basicDiffuse[] =
        "#version 330 core\n\
        layout(location = 0) in vec3 aPos;\n\
        layout(location = 1) in vec2 aTexCoords;\n\
        out vec2 TexCoords;\n\
        // ģ����ͼͶӰ����\n\
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
		// ����һ����������ͼ\n\
		uniform sampler2D texture_diffuse1;\n\
		void main()\n\
		{\n\
		    FragColor = texture(texture_diffuse1, TexCoords);\n\
		    //FragColor = vec4(1,0,0,1);\n\
		}";
}