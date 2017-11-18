#include <shader.h>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace std;
using namespace ginkgo;

Shader Shader::basicDiffuse;

Shader::Shader(const char* vsPath, const char* fsPath)
{
    // ��ȡ����
    std::string vsCode = readCode(vsPath);
    std::string fsCode = readCode(fsPath);

    // ����
    unsigned int vs = compileShader(vsCode.c_str(), GL_VERTEX_SHADER);
    unsigned int fs = compileShader(fsCode.c_str(), GL_FRAGMENT_SHADER);

    // ����
    int success;
    char log[512];
    id = glCreateProgram();
    glAttachShader(id, vs);
    glAttachShader(id, fs);
    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(id, 512, NULL, log);
        cout << "Shader[" << fsPath << "]���Ӵ���:" << endl << log << endl;
    }
    // �ͷ�
    glDeleteShader(vs);
    glDeleteShader(fs);
}

Shader::~Shader()
{
    //if (id)glDeleteProgram(id);
}

unsigned int Shader::getID()
{
    return id;
}

std::string Shader::readCode(const char* path)
{
    FILE* fp;
    std::string code = "";

    // ���ļ�
    if (fopen_s(&fp, path, "r"))
    {
        cout << "Shader[" << path << "]��ȡ����" << endl;
        return code;
    }
    // ��ȡ����
    char buff[512];
    while (fgets(buff, 512, fp))
    {
        code.append(buff);
    }
    fclose(fp);
    //code.append("\n\0");
    return code;
}

unsigned int Shader::compileShader(const char* code, unsigned int shaderType)
{
    int success;
    char log[512];
    unsigned shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &code, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, log);
        cout << "Shader[" << shaderType << "]�������:" << endl << log << endl;
        return 0;
    }
    return shader;
}

void Shader::use()
{
    glUseProgram(id);
}

void Shader::setBool(const char* name, bool value) const
{
    glUniform1i(glGetUniformLocation(id, name), (int)value);
}

void Shader::setInt(const char* name, int value) const
{
    glUniform1i(glGetUniformLocation(id, name), value);
}

void Shader::setFloat(const char* name, float value) const
{
    glUniform1f(glGetUniformLocation(id, name), value);
}

void Shader::setMat4(const char* name, glm::mat4 matrix) const
{
    glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

///<summary>����Vec2��Uniformֵ</summary>
void Shader::setVec2(const char* name, glm::vec2 value) const
{
    glUniform2f(glGetUniformLocation(id, name), value.x, value.y);
}

///<summary>����Vec3��Uniformֵ</summary>
void Shader::setVec3(const char* name, glm::vec3 value) const
{
    glUniform3f(glGetUniformLocation(id, name), value.x, value.y, value.z);
}

///<summary>����Vec4��Uniformֵ</summary>
void Shader::setVec4(const char* name, glm::vec4 value) const
{
    glUniform4f(glGetUniformLocation(id, name), value.x, value.y, value.z, value.w);
}

// �ڽ���ɫ��
void Shader::buildBuiltinShaders()
{
    basicDiffuse = Shader("basicDiffuse");
}

Shader::Shader(string type)
{
    const char* vsCode;
    const char* fsCode;

    if (type == "basicDiffuse")
    {
        vsCode = vs_basicDiffuse;
        fsCode = fs_basicDiffuse;
    }

    // ����
    unsigned int vs = compileShader(vsCode, GL_VERTEX_SHADER);
    unsigned int fs = compileShader(fsCode, GL_FRAGMENT_SHADER);

    // ����
    int success;
    char log[512];
    id = glCreateProgram();
    glAttachShader(id, vs);
    glAttachShader(id, fs);
    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(id, 512, NULL, log);
        cout << "Shader[" << type << "]���Ӵ���:" << endl << log << endl;
    }
    // �ͷ�
    glDeleteShader(vs);
    glDeleteShader(fs);
}
