// ;
#include "SceneHiererchyPanel.h"

#include "exw\scene\Component.h"

#include <imgui.h>
#include <imgui_internal.h>

namespace exw
{
    #pragma region Utils Function
    template <typename T, typename UIFunction>
    static void draw_component(const std::string& _name, Entity _entity, UIFunction _function)
    {
        const ImGuiTreeNodeFlags treeNodeFlags =
            ImGuiTreeNodeFlags_DefaultOpen
            | ImGuiTreeNodeFlags_Framed
            | ImGuiTreeNodeFlags_SpanAvailWidth
            | ImGuiTreeNodeFlags_AllowItemOverlap
            | ImGuiTreeNodeFlags_FramePadding;
        if (_entity.has_component<T>())
        {
            auto& component = _entity.get_component<T>();
            ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2 { 4, 4 });
            float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
            ImGui::Separator();

            bool removeComponent = false;
            if (ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, _name.c_str()))
            {
                ImGui::PopStyleVar();

                ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
                if (ImGui::Button("+", ImVec2 { lineHeight, lineHeight }))
                {
                    ImGui::OpenPopup("popup_ComponentSettings");
                }

                if (ImGui::BeginPopup("popup_ComponentSettings"))
                {
                    if (ImGui::MenuItem("Remove component"))
                    {
                        removeComponent = true;
                    }

                    ImGui::EndPopup();
                }

                _function(component);
                ImGui::TreePop();
            }

            if (removeComponent)
                _entity.remove_component<T>();
        }
    }

    static void draw_vector3_control(const std::string& _label, maths::vector3& _values, float _defaultValue = 0.0f, float _columnWidth = 100.0f)
    {
        ImGuiIO& io = ImGui::GetIO();
        auto boldFont = io.Fonts->Fonts[0];

        ImGui::PushID(_label.c_str());

        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, _columnWidth);
        ImGui::Text(_label.c_str());
        ImGui::NextColumn();

        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2 { 0, 0 });

        float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

        // x = red;
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4 { 0.8f, 0.1f, 0.15f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4 { 0.9f, 0.2f, 0.2f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4 { 0.8f, 0.1f, 0.15f, 1.0f });
            ImGui::PushFont(boldFont);
            if (ImGui::Button("X", buttonSize))
                _values.x = _defaultValue;
            ImGui::PopFont();
            ImGui::PopStyleColor(3);

            ImGui::SameLine();
            ImGui::DragFloat("##X", &_values.x, 0.1f, 0.0f, 0.0f, "%.2f");
            ImGui::PopItemWidth();
        }

        // y = green;
        {
            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4 { 0.2f, 0.7f, 0.2f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4 { 0.3f, 0.8f, 0.3f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4 { 0.2f, 0.7f, 0.2f, 1.0f });
            ImGui::PushFont(boldFont);
            if (ImGui::Button("Y", buttonSize))
                _values.y = _defaultValue;
            ImGui::PopFont();
            ImGui::PopStyleColor(3);

            ImGui::SameLine();
            ImGui::DragFloat("##Y", &_values.y, 0.1f, 0.0f, 0.0f, "%.2f");
            ImGui::PopItemWidth();
        }

        // z = blue;
        {
            ImGui::SameLine();
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4 { 0.1f, 0.25f, 0.8f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4 { 0.2f, 0.35f, 0.9f, 1.0f });
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4 { 0.1f, 0.25f, 0.8f, 1.0f });
            ImGui::PushFont(boldFont);
            if (ImGui::Button("Z", buttonSize))
                _values.z = _defaultValue;
            ImGui::PopFont();
            ImGui::PopStyleColor(3);

            ImGui::SameLine();
            ImGui::DragFloat("##Z", &_values.z, 0.1f, 0.0f, 0.0f, "%.2f");
            ImGui::PopItemWidth();
        }

        ImGui::PopStyleVar();

        ImGui::Columns(1);

        ImGui::PopID();
    }
    #pragma endregion

    SceneHierarchyPanel::SceneHierarchyPanel(const refs::ref<Scene>& _scene)
    {
        set_context(_scene);
    }
    void SceneHierarchyPanel::on_gui_render()
    {
        ImGui::Begin("Scene Hierarchy");
        {
            m_Context->m_Registry.each([&] (auto _entityId)
            {
                Entity entity { _entityId, m_Context.get() };
                draw_entity_node(entity);
            });

            if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
            {
                m_Selection_context = {};
            }

            if (ImGui::BeginPopupContextWindow(0, 1, false))
            {
                if (ImGui::MenuItem("Create Empty Entity"))
                {
                    m_Context->create_entity("Empty Entity");
                }
                ImGui::EndPopup();
            }
        }
        ImGui::End();

        ImGui::Begin("Properties");
        {
            if (m_Selection_context)
            {
                draw_components(m_Selection_context);
            }
        }
        ImGui::End();
    }

    void SceneHierarchyPanel::set_context(const refs::ref<Scene>& _context)
    {
        m_Context = _context;
        m_Selection_context = {};
    }

    void SceneHierarchyPanel::draw_entity_node(Entity _entity)
    {
        auto& tag = _entity.get_component<TagComponent>().Tag;

        ImGuiTreeNodeFlags flags =
            ((m_Selection_context == _entity) ? ImGuiTreeNodeFlags_Selected : 0)
            | ImGuiTreeNodeFlags_OpenOnArrow
            | ImGuiTreeNodeFlags_SpanAvailWidth;

        bool entityDeleted = false;
        if (ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)_entity, flags, tag.c_str()))
        {
            if (ImGui::IsItemClicked())
            {
                m_Selection_context = _entity;
            }

            if (ImGui::BeginPopupContextItem())
            {
                if (ImGui::MenuItem("Delete Entity"))
                {
                    entityDeleted = true;
                }
                ImGui::EndPopup();
            }

            ImGuiTreeNodeFlags flags2 = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
            if (ImGui::TreeNodeEx((void*)9817239, flags2, tag.c_str()))
            {
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }

        if (entityDeleted)
        {
            m_Context->destroy_entity(_entity);
            if (m_Selection_context == _entity)
                m_Selection_context = {};
        }
    }

    void SceneHierarchyPanel::draw_components(Entity _entity)
    {
        if (_entity.has_component<TagComponent>())
        {
            auto& tag = _entity.get_component<TagComponent>().Tag;

            char buffer[256];
            memset(buffer, 0, sizeof(buffer));
            strcpy_s(buffer, sizeof(buffer), tag.c_str());
            if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
            {
                tag = std::string(buffer);
            }
        }
        else {}

        ImGui::SameLine();
        ImGui::PushItemWidth(-1);

        if (ImGui::Button("Add Component"))
        {
            ImGui::OpenPopup("popup_AddComponent");
        }

        if (ImGui::BeginPopup("popup_AddComponent"))
        {
            if (ImGui::MenuItem("Camera"))
            {
                m_Selection_context.add_component<CameraComponent>();
                ImGui::CloseCurrentPopup();
            }

            if (ImGui::MenuItem("Sprite Renderer"))
            {
                m_Selection_context.add_component<SpriteRendererComponent>();
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }

        ImGui::PopItemWidth();

        draw_component<TransformComponent>("Transform", _entity, [] (TransformComponent& _component)
        {
            draw_vector3_control("Translation", _component.Translation);

            maths::vector3 rotation = {
                maths::to_degrees(_component.Rotation.x),
                maths::to_degrees(_component.Rotation.y),
                maths::to_degrees(_component.Rotation.z)
            };
            draw_vector3_control("Rotation", rotation);
            _component.Rotation = {
                maths::to_radians(rotation.x),
                maths::to_radians(rotation.y),
                maths::to_radians(rotation.z)
            };

            draw_vector3_control("Scale", _component.Scale, 1.0f);
        });

        draw_component<CameraComponent>("Camera", _entity, [] (CameraComponent& _component)
        {
            auto& camera = _component.Camera;

            ImGui::Checkbox("Primary", &_component.IsPrimary);

            const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
            const char* currentProjectionTypeString = projectionTypeStrings[(int)camera.get_projection_type()];
            if (ImGui::BeginCombo("Projection", currentProjectionTypeString))
            {
                for (int i = 0; i < 2; i++)
                {
                    bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
                    if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
                    {
                        currentProjectionTypeString = projectionTypeStrings[i];
                        camera.set_projection_type((Camera::ProjectionType)i);
                    }

                    if (isSelected)
                    {
                        ImGui::SetItemDefaultFocus();
                    }
                }

                ImGui::EndCombo();
            }

            if (camera.get_projection_type() == Camera::ProjectionType::Perspective)
            {
                float perspectiveVerticalFov = glm::degrees(camera.get_perspective_vertical_fov());
                if (ImGui::DragFloat("Vertical FOV", &perspectiveVerticalFov))
                    camera.set_perspective_vertical_fov(glm::radians(perspectiveVerticalFov));

                float perspectiveNear = camera.get_perspective_near_clip();
                if (ImGui::DragFloat("Near", &perspectiveNear))
                    camera.set_perspective_near_clip(perspectiveNear);

                float perspectiveFar = camera.get_perspective_far_clip();
                if (ImGui::DragFloat("Far", &perspectiveFar))
                    camera.set_perspective_far_clip(perspectiveFar);
            }
            else if (camera.get_projection_type() == SceneCamera::ProjectionType::Orthographic)
            {
                float orthoSize = camera.get_orthographic_size();
                if (ImGui::DragFloat("Size", &orthoSize))
                    camera.set_orthographic_size(orthoSize);

                float orthoNear = camera.get_orthographic_near_clip();
                if (ImGui::DragFloat("Near", &orthoNear))
                    camera.set_orthographic_near_clip(orthoNear);

                float orthoFar = camera.get_orthographic_far_clip();
                if (ImGui::DragFloat("Far", &orthoFar))
                    camera.set_orthographic_far_clip(orthoFar);

                ImGui::Checkbox("Fixed Aspect Ratio", &_component.IsFixedAspectRatio);
            }
        });

        draw_component<SpriteRendererComponent>("Sprite Renderer", _entity, [] (auto& _component)
        {
            ImGui::ColorEdit4("Color", &_component.Color.x);
        });

    }
}
