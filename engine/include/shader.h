#pragma once

#include <string>
#include <glm/glm.hpp>

//着色器
class Shader
{
public:
    //空的着色器，由于几个内建的着色器是静态变量，但是编译需要等到初始化完毕所以先调用这个空的构建函数
    Shader() {id=0;}
    //实例化内建着色器
    //内建着色器的名字
    Shader(std::string name);
    //顶点着色程序文件的路径
    //片段着色程序文件的路径
    Shader(const char* vsPath, const char* fsPath);
    //使用该着色器
    void use();
    //从GPU释放该着色器的资源
    void release();
    //设置bool型(其实是int)uniform
    void setBool(const char* name, bool value) const;
    //设置int型uniform
    void setInt(const char* name, int value) const;
    //设置float型uniform
    void setFloat(const char* name, float value) const;
    //设置Mat4型uniform
    void setMat4(const char* name, glm::mat4 matrix) const;
    //设置vec2型uniform
    void setVec2(const char* name, glm::vec2 value) const;
    //设置vec3型uniform
    void setVec3(const char* name, glm::vec3 value) const;
    //设置vec4型uniform
    void setVec4(const char* name, glm::vec4 value) const;
    //获取着色器的ID
    unsigned int getID();
    // 储存使用这个着色器的相机的Projection和view矩阵,(在获取物体屏幕坐标时可以用到)
    glm::mat4 projection;
    glm::mat4 view;
    //编译内建着色器
    static void buildBuiltinShaders();
    /// 以下是一些内建的基本着色器
    //基础着色器，只有一个纹理贴图，没有光照
    static Shader basicDiffuse;
private:
    //着色器程序在opengl中的id
    unsigned int id;
    //读取代码文件内容
    std::string readCode(const char* path);
    //编译着色器
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
