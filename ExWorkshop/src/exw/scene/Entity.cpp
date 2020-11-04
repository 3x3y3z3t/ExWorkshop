// ;
#include "expch.h"
#include "Entity.h"

namespace exw
{
    Entity::Entity(entt::entity _handle, Scene* _scene)
        : m_Handle(_handle), m_Scene(_scene)
    {}
}
