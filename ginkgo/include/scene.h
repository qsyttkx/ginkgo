#pragma once

#include <macros.h>
#include <node.h>
#include <camera.h>

namespace ginkgo
{
    /// <summary>场景</summary>
    /// <para>一个游戏场景，也作为其场景内容的根节点</para>
    class DLL Scene :public Node
    {
    public:
        /// <summary>构造一个场景</summary>
        Scene();
        /// <summary>析构场景</summary>
        virtual ~Scene();
        /// <summary>主摄像机</summary>
        Camera* mainCamera;
        /// <summary>UI摄像机</summary>
        Camera* uiCamera;
        /// <summary>渲染</summary>
        virtual void update(float dt);
        /// <summary>背景颜色（glClearColor）</summary>
        glm::vec3 backgroundColor;
        // UI节点
        Node* ui;
    };
}