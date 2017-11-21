#pragma once

#include <macros.h>
#include <node.h>
#include <camera.h>

namespace ginkgo
{
    class DLL Scene :public Node
    {
    public:
        Scene();
		virtual ~Scene();
        Camera* mainCamera;
        virtual void render();
        glm::vec3 backgroundColor;
    };
}