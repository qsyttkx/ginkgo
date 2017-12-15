#pragma once

#include <macros.h>
#include <node.h>
#include <camera.h>
#include <texture.h>

namespace ginkgo
{
    //场景
    //一个游戏场景，也作为其场景内容的根节点
    class DLL Layer :public Node
    {
    public:
        //构造一个场景
        Layer(Node* parent, float width = 0, float height = 0);
        //析构场景
        virtual ~Layer();
        //主摄像机
        Camera* camera;
        // 渲染到纹理
        void renderToTexture(float dt);
        //渲染
        virtual void update(float dt);
        virtual void renderHeader();
        //背景颜色（glClearColor）
        glm::vec4 backgroundColor;
        // 本层渲染到的纹理
        Texture framebuffertexture;
        //顶点数组、缓冲对象
        GLuint VAO, VBO,framebuffer,renderbuffer;
    protected:
        // 为了避免同一个变换被重复用两次，我们这里对layer的子节点屏蔽layer的Transform
        virtual glm::mat4 getGlobalTransform();
        float width, height;
    };
}