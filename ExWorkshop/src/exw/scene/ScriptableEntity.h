// ;
#pragma once

#include "Entity.h"
#include "exw\utils\Timestep.h"

namespace exw
{
    class ScriptableEntity
    {
    public:
        virtual ~ScriptableEntity() {}

    public:
        template <typename T>
        T& get_component()
        {
            return m_Entity.get_component<T>();
        }

        template <typename T>
        bool has_component()
        {
            return m_Entity.has_component<T>();
        }

    protected:
        virtual void create() {}
        virtual void destroy() {}
        virtual void update(Timestep _ts) {}

    private:
        Entity m_Entity;
        friend class Scene;
    };
}
