#pragma once

#include <node.h>
#include <camera.h>

namespace ginkgo
{
    class DLL Scene :public Node
    {
    public:
        Scene();
        Camera* mainCamera;
        virtual void render();
        glm::vec3 backgroundColor;
    };
}