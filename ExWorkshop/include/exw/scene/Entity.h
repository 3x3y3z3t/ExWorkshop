// ;
#pragma once

#include "Scene.h"

#include "exw\Common.h"
#include "exw\utils\Timestep.h"

#include <entt.hpp>

namespace exw
{
    class Entity
    {
    public:
        Entity() = default;
        Entity(const Entity& _entity) = default;
        Entity(entt::entity _handle, Scene* _scene);
        virtual ~Entity() = default;

    public:
        template <typename T, typename... Args>
        T& add_component(Args&&... _args)
        {
            EXW_ASSERT(!has_component<T>(), "This entity already has this component.");
            T& component = m_Scene->m_Registry.emplace<T>(m_Handle, std::forward<Args>(_args)...);
            m_Scene->on_component_added<T>(*this, component);
            return component;
        }

        template <typename T>
        void remove_component()
        {
            EXW_ASSERT(has_component<T>(), "This entity does not have this component.");
            m_Scene->m_Registry.remove<T>(m_Handle);
            m_Scene->on_component_removed(*this);
        }

        template <typename T>
        T& get_component() const
        {
            EXW_ASSERT(has_component<T>(), "This entity does not have this component.");
            return m_Scene->m_Registry.get<T>(m_Handle);
        }

        template <typename T>
        bool has_component() const
        {
            return m_Scene->m_Registry.has<T>(m_Handle);
        }

        uint32_t get_id() const { return (uint32_t)m_Handle; }

        operator bool() const { return m_Handle != entt::null; }
        operator entt::entity() const { return m_Handle; }
        operator uint32_t() const { return (uint32_t)m_Handle; }

        bool operator==(const Entity& _other) const { return m_Handle == _other.m_Handle && m_Scene == _other.m_Scene; }
        bool operator!=(const Entity& _other) const { return !(*this == _other); }

    private:
        entt::entity m_Handle { entt::null };
        Scene* m_Scene = nullptr;
    };
}
