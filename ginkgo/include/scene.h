#pragma once

#include <macros.h>
#include <node.h>
#include <camera.h>
#include <layer.h>

namespace ginkgo
{
    //场景
    //一个游戏场景，也作为其场景内容的根节点
    class DLL Scene :public Node
    {
    public:
        //构造一个场景
        Scene();
        //析构场景
        virtual ~Scene();
        //渲染
        virtual void update(float dt);
        //背景颜色（glClearColor）
        glm::vec3 backgroundColor;
        glm::mat4 matProjection;
        glm::mat4 matView;
        Layer* root;
    };
}