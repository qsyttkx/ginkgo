#include <shader.h>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>

using namespace std;

Shader Shader::basicDiffuse;

Shader::Shader(const char *vsPath, const char *fsPath)
{
    // 读取代码
    std::string vsCode = readCode(vsPath);
    std::string fsCode = readCode(fsPath);

    // 编译
    unsigned int vs = compileShader(vsCode.c_str(), GL_VERTEX_SHADER);
    unsigned int fs = compileShader(fsCode.c_str(), GL_FRAGMENT_SHADER);

    // 链接
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
        cout << "Shader[" << fsPath << "]link error:" << endl
             << log << endl;
    }
    // 释放
    glDeleteShader(vs);
    glDeleteShader(fs);
}

void Shader::release()
{
    if (id)
        glDeleteProgram(id);
}

unsigned int Shader::getID()
{
    return id;
}

std::string Shader::readCode(const char *path)
{
    std::string code;
    fstream file(path);
    if (!file.is_open())
    {
        file.close();
        cerr << "Can't read shader file: " << path << "!" << endl;
        return code;
    }

    code = string(istreambuf_iterator<char>(file), istreambuf_iterator<char>());
    file.close();
    return code;
}

unsigned int Shader::compileShader(const char *code, unsigned int shaderType)
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
        cout << "Shader[" << shaderType << "]compile error:" << endl
             << log << endl;
        return 0;
    }
    return shader;
}

void Shader::use()
{
    glUseProgram(id);
}

void Shader::setBool(const char *name, bool value) const
{
    glUniform1i(glGetUniformLocation(id, name), (int)value);
}

void Shader::setInt(const char *name, int value) const
{
    glUniform1i(glGetUniformLocation(id, name), value);
}

void Shader::setFloat(const char *name, float value) const
{
    glUniform1f(glGetUniformLocation(id, name), value);
}

void Shader::setMat4(const char *name, glm::mat4 matrix) const
{
    glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

//设置Vec2型Uniform值
void Shader::setVec2(const char *name, glm::vec2 value) const
{
    glUniform2f(glGetUniformLocation(id, name), value.x, value.y);
}

//设置Vec3型Uniform值
void Shader::setVec3(const char *name, glm::vec3 value) const
{
    glUniform3f(glGetUniformLocation(id, name), value.x, value.y, value.z);
}

//设置Vec4型Uniform值
void Shader::setVec4(const char *name, glm::vec4 value) const
{
    glUniform4f(glGetUniformLocation(id, name), value.x, value.y, value.z, value.w);
}

void Shader::buildBuiltinShaders()
{
    basicDiffuse = Shader("basicDiffuse");
}

Shader::Shader(string name)
{
    const char *vsCode;
    const char *fsCode;

    if (name == "basicDiffuse")
    {
        vsCode = vs_basicDiffuse;
        fsCode = fs_basicDiffuse;
    }

    // 编译
    unsigned int vs = compileShader(vsCode, GL_VERTEX_SHADER);
    unsigned int fs = compileShader(fsCode, GL_FRAGMENT_SHADER);

    // 链接
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
        cout << "Shader[" << name << "]link error:" << endl
             << log << endl;
    }
    // 释放
    glDeleteShader(vs);
    glDeleteShader(fs);
}
