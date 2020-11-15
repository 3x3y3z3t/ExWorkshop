// ;
#pragma once

#include <ExWorkshop.h>

#include "gui\SceneHiererchyPanel.h"

namespace exw
{
    class EditorLayer : public Layer
    {
    public:
        EditorLayer();

        virtual void attach() override;
        virtual void detach() override;
        virtual void update(Timestep _ts) override;
        virtual void render_gui() override;

        virtual void on_event(event::Event& _event) override;
        
        bool new_scene();
        bool open_scene();
        bool save_scene(bool _saveAs = false);

    private:
        bool m_Viewport_focused = false;
        bool m_Viewport_hovered = false;
        maths::vector2 m_Viewport_size = { 0.0f, 0.0f };

        refs::ref<graphics::Framebuffer> m_Framebuffer;

        refs::ref<Scene> m_Active_scene;
        Entity m_Square;
        Entity m_Camera;

        SceneHierarchyPanel m_Scene_hierarchy_panel;
    };
}
