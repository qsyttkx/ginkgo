#pragma once

#include <macros.h>
#include <node.h>
#include <camera.h>
#include <texture.h>

namespace ginkgo
{
    //����
    //һ����Ϸ������Ҳ��Ϊ�䳡�����ݵĸ��ڵ�
    class DLL Layer :public Node
    {
    public:
        //����һ������
        Layer(Node* parent, float width = 0, float height = 0);
        //��������
        virtual ~Layer();
        //�������
        Camera* camera;
        // ��Ⱦ������
        void renderToTexture(float dt);
        //��Ⱦ
        virtual void update(float dt);
        virtual void renderHeader();
        //������ɫ��glClearColor��
        glm::vec4 backgroundColor;
        // ������Ⱦ��������
        Texture framebuffertexture;
        //�������顢�������
        GLuint VAO, VBO,framebuffer,renderbuffer;
    protected:
        // Ϊ�˱���ͬһ���任���ظ������Σ����������layer���ӽڵ�����layer��Transform
        virtual glm::mat4 getGlobalTransform();
        float width, height;
    };
}