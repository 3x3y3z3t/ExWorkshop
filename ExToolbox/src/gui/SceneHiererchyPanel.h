// ;
#pragma once

#include "exw\Common.h"

#include "exw\scene\Entity.h"
#include "exw\scene\Scene.h"

namespace exw
{
    class SceneHierarchyPanel
    {
    public:
        SceneHierarchyPanel() = default;
        SceneHierarchyPanel(const refs::ref<Scene>& _scene);

    public:
        void on_gui_render();

        void set_context(const refs::ref<Scene>& _context);
    private:
        void draw_entity_node(const Entity& _entity);
        void draw_components(const Entity& _entity);

    private:
        refs::ref<Scene> m_Context;
        Entity m_Selection_context;
    };

}
