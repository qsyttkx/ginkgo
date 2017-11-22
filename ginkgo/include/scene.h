#pragma once

#include <macros.h>
#include <node.h>
#include <camera.h>

namespace ginkgo
{
    /// <summary>����</summary>
    /// <para>һ����Ϸ������Ҳ��Ϊ�䳡�����ݵĸ��ڵ�</para>
    class DLL Scene :public Node
    {
    public:
        /// <summary>����һ������</summary>
        Scene();
        /// <summary>��������</summary>
		virtual ~Scene();
        /// <summary>�������</summary>
        Camera* mainCamera;
        /// <summary>��Ⱦ</summary>
        virtual void render();
        /// <summary>������ɫ��glClearColor��</summary>
        glm::vec3 backgroundColor;
    };
}