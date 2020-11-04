// 
#pragma once

#include "exw\Common.h"
#include "exw\utils\Timestep.h"

#include <entt.hpp>

namespace exw
{
    class Entity;

    class Scene
    {
    public:
        Scene();
        ~Scene();

    public:
        Entity create_entity(const std::string& _name = "");
        void destroy_entity(Entity _entity);

        void on_scene_play();
        void on_scene_stop();

        void update(Timestep _ts);
        void on_viewport_resize(uint32_t _width, uint32_t _height);
    private:
        template <typename T>
        void on_component_added(Entity _entity, T& _component);
        void on_component_removed(Entity _entity);

    public:
        friend class Entity;
        friend class SceneSerializer;
        friend class SceneHierarchyPanel;
    private:
        entt::registry m_Registry;
        uint32_t m_Viewport_width = 0U;
        uint32_t m_Viewport_height = 0U;
    };
}
