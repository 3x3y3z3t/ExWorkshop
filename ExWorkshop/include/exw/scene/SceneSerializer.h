// ;
#pragma once

#include "exw\Common.h"

#include "Scene.h"

namespace exw
{
    class SceneSerializer
    {
    public:
        SceneSerializer(const refs::ref<Scene>& _scene);

    public:
        bool serialize(const std::string& _filepath);

        bool deserialize(const std::string& _filepath);

    private:
        refs::ref<Scene> m_Scene;
    };
}
