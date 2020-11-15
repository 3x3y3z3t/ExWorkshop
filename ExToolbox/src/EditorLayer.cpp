// ;
#include "EditorLayer.h"

#include <imgui.h>

namespace exw
{
    EditorLayer::EditorLayer()
        : Layer("editor_layer")
    {}

    void EditorLayer::attach()
    {
        EXW_PROFILE_FUNCTION();
        exw::graphics::RenderCommand::set_clear_color({ 0.1f, 0.1f, 0.1f, 1.0f });

        graphics::FramebufferSpec spec;
        spec.Width = 1600U;
        spec.Height = 900U;
        m_Framebuffer = graphics::Framebuffer::create(spec);

        new_scene();
        //m_Active_scene = exw::refs::create_ref<exw::Scene>();

        m_Square = m_Active_scene->create_entity("Square");
        m_Square.add_component<exw::SpriteRendererComponent>(exw::maths::vector4 { 0.0f, 1.0f, 1.0f, 1.0f });
        auto& transform = m_Square.get_component<exw::TransformComponent>();

        m_Camera = m_Active_scene->create_entity("Camera");
        auto& cameraComp = m_Camera.add_component<exw::CameraComponent>(true);

        //m_Scene_hierarchy_panel.set_context(m_Active_scene);

    }

    void EditorLayer::detach()
    {
        EXW_PROFILE_FUNCTION();

    }

    void EditorLayer::update(Timestep _ts)
    {
        EXW_PROFILE_FUNCTION();

        // resize;
        {
            graphics::FramebufferSpec spec = m_Framebuffer->get_spec();
            if ((m_Viewport_size.x > 0.0f && m_Viewport_size.y > 0.0f) &&
                (spec.Width != m_Viewport_size.x || spec.Height != m_Viewport_size.y))
            {
                m_Framebuffer->resize((uint32_t)m_Viewport_size.x, (uint32_t)m_Viewport_size.y);
                //m_Camera_controller.resize(m_Viewport_size.x, m_Viewport_size.y);
                m_Active_scene->on_viewport_resize((uint32_t)m_Viewport_size.x, (uint32_t)m_Viewport_size.y);
            }
        }

        // logic update;
        {
            using namespace exw;
            if (m_Viewport_focused)
            {
                //m_Camera_controller.on_update(_ts);
            }

        }

        // render;
        {
            EXW_PROFILE_SCOPE("Sandbox Rendering");
            using namespace exw;
            using namespace exw::graphics;

            Renderer2D::reset_stats();
            m_Framebuffer->bind();
            RenderCommand::clear();

            m_Active_scene->update(_ts);




            m_Framebuffer->unbind();
        }

    }

    void EditorLayer::render_gui()
    {
        EXW_PROFILE_FUNCTION();

		static bool enableDockspace = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &enableDockspace, window_flags);
        {
            ImGui::PopStyleVar();

            if (opt_fullscreen)
            {
                // pop _WindowRounding = 0.0f and _WindowBorderSize = 0.0f;
                ImGui::PopStyleVar(2);
            }

            // DockSpace
            ImGuiIO& io = ImGui::GetIO();
            ImGuiStyle& style = ImGui::GetStyle();
            float minWinSizeX = style.WindowMinSize.x;
            style.WindowMinSize.x = 370.0f;
            if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
            {
                ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
                ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
            }

            style.WindowMinSize.x = minWinSizeX;

            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("File"))
                {
                    // Disabling fullscreen would allow the window to be moved to the front of other windows, 
                    // which we can't undo at the moment without finer window depth/z control.
                    //ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);1
                    if (ImGui::MenuItem("New", "Ctrl+N"))
                    {
                        new_scene();
                    }

                    if (ImGui::MenuItem("Open...", "Ctrl+O"))
                    {
                        open_scene();
                    }

                    if (ImGui::MenuItem("Save", "Ctrl+S"))
                    {
                        save_scene(false);
                    }
                    if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
                    {
                        save_scene(true);
                    }

                    if (ImGui::MenuItem("Exit", "Alt+F4"))
                    {
                        Application::get().close();
                    }
                    ImGui::EndMenu();
                }

                ImGui::EndMenuBar();
            }

            m_Scene_hierarchy_panel.on_gui_render();

            ImGui::Begin("Stats");
            {
                auto stats = graphics::Renderer2D::get_stats();
                ImGui::Text("Renderer2D Stats:");
                ImGui::Text("Draw Calls: %d", stats.DrawCalls);
                ImGui::Text("Quads: %d", stats.QuadCount);
                ImGui::Text("Vertices: %d", stats.get_vertex_count());
                ImGui::Text("Indices: %d", stats.get_index_count());
            }
            ImGui::End();

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2 { 0, 0 });
            ImGui::Begin("Viewport");
            {
                m_Viewport_focused = ImGui::IsWindowFocused();
                m_Viewport_hovered = ImGui::IsWindowHovered();
                Application::get().get_gui_layer()->block_events(!m_Viewport_focused || !m_Viewport_hovered);

                ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
                m_Viewport_size = { viewportPanelSize.x, viewportPanelSize.y };

                uint64_t textureID = m_Framebuffer->get_color_attachment_renderer_id();
                ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2 { m_Viewport_size.x, m_Viewport_size.y }, ImVec2 { 0, 1 }, ImVec2 { 1, 0 });
            }
            ImGui::End();
            ImGui::PopStyleVar();
        }
		ImGui::End();
    }

    void EditorLayer::on_event(event::Event& _event)
    {
        EXW_PROFILE_FUNCTION();

        using namespace event;
        EventDispatcher dispatcher(_event);

        dispatcher.dispatch<KeyPressedEvent>([&] (KeyPressedEvent& _evt)
        {
            if (_evt.get_repeat_count() > 0U)
            {
                return false;
            }

            if (_evt.get_keycode() == Keys::N
                && (Input::is_key_pressed(Keys::LeftControl) || Input::is_key_pressed(Keys::RightControl)))
            {
                new_scene();
                return true;
            }

            if ((Input::is_key_pressed(Keys::LeftControl) || Input::is_key_pressed(Keys::RightControl))
                && _evt.get_keycode() == Keys::O)
            {
                open_scene();
                return true;
            }

            if ((Input::is_key_pressed(Keys::LeftControl) || Input::is_key_pressed(Keys::RightControl))
                && _evt.get_keycode() == Keys::S)
            {
                save_scene(Input::is_key_pressed(Keys::LeftShift) || Input::is_key_pressed(Keys::RightShift));
                return true;
            }

            return false;
        });



        // ==========

        dispatcher.dispatch<MouseButtonPressedEvent>([&] (MouseButtonPressedEvent& _evt)
        {
            auto& entity = m_Active_scene->create_entity();
            entity.add_component<SpriteRendererComponent>(maths::vector4 { 1.0f, 1.0f, 0.0f, 1.0f });

            vec2 cpos = Input::get_cursor_position();
            auto& transform = entity.get_component<TransformComponent>();
            transform.Translation = { cpos.x, cpos.y, 0.0f };

            return true;
        });

    }

    bool EditorLayer::new_scene()
    {
        m_Active_scene = refs::create_ref<Scene>();
        m_Active_scene->on_viewport_resize((uint32_t)m_Viewport_size.x, (uint32_t)m_Viewport_size.y);
        m_Scene_hierarchy_panel.set_context(m_Active_scene);
        return true;
    }

    bool EditorLayer::open_scene()
    {
        std::string filepath = utils::FileDialogs::open_file("Exw Scene (*.exs)\0*.exs\0");
        if (!filepath.empty())
        {
            m_Active_scene = refs::create_ref<Scene>();
            m_Active_scene->on_viewport_resize((uint32_t)m_Viewport_size.x, (uint32_t)m_Viewport_size.y);
            m_Scene_hierarchy_panel.set_context(m_Active_scene);

            //SceneSerializer serializer(m_Active_scene);
            //serializer.deserialize(filepath);
            return true;
        }

        return false;
    }

    bool EditorLayer::save_scene(bool _saveAs)
    {
        if (_saveAs)
        {
            std::string filepath = utils::FileDialogs::save_file("Exw Scene (*.exs)\0*.exs\0");
            if (!filepath.empty())
            {
                //SceneSerializer serializer(m_Active_scene);
                //serializer.serialize(filepath);
                return true;
            }

            return false;
        }

        EXW_LOG_WARNING("'Save' is currently not supported.");
        return false;
    }
}
