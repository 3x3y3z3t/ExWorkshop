// ;
#include "expch.h"
#include "Scene.h"

#include "Entity.h"
#include "Component.h"
#include "exw\graphics\Renderer2D.h"
#include "exw\maths\matrix4.h"
#include "exw\maths\math_utils.h"

namespace exw
{
    Scene::Scene()
    {}

    Scene::~Scene()
    {}

    Entity Scene::create_entity(const std::string& _name)
    {
        Entity entity = { m_Registry.create(), this };
        entity.add_component<TransformComponent>();
        auto& tag = entity.add_component<TagComponent>();
        tag.Tag = _name.empty() ? "Entity" : _name;
        return entity;
    }

    void Scene::destroy_entity(Entity _entity)
    {
        m_Registry.destroy(_entity);
    }

    void Scene::on_scene_play()
    {}

    void Scene::on_scene_stop()
    {}

    void Scene::update(Timestep _ts)
    {
        // destroy dead entity;
        //{
        //    m_Registry.view<TagComponent>().each([&] (auto _entity, auto& _component)
        //    {
        //        if (_component.Tag == "DeadEntity")
        //        {
        //            m_Registry.destroy(_entity);
        //        }
        //    });
        //}

        // update camera;
        Camera* mainCam = nullptr;
        maths::matrix4 camTransform;
        {
            auto view = m_Registry.view<TransformComponent, CameraComponent>();
            for (auto entity : view)
            {
                auto[transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
                if (camera.IsPrimary)
                {
                    mainCam = &camera.Camera;
                    camTransform = transform.get_transform();
                    break;
                }
            }
        }

        // render;
        if (mainCam != nullptr)
        {
            graphics::Renderer2D::begin_scene(*mainCam, camTransform);

            auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
            for (auto entity : group)
            {
                auto[transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
                graphics::Renderer2D::draw_quad(transform.get_transform(), sprite.Color);
            }

            graphics::Renderer2D::end_scene();


        }

    }

    void Scene::on_viewport_resize(uint32_t _width, uint32_t _height)
    {
        m_Viewport_width = _width;
        m_Viewport_height = _height;

        auto view = m_Registry.view<CameraComponent>();
        for (auto entity : view)
        {
            auto& cameraComponent = view.get<CameraComponent>(entity);
            if (!cameraComponent.IsFixedAspectRatio)
            {
                cameraComponent.Camera.set_viewport_size(_width, _height);
            }
        }
    }

    void Scene::on_component_removed(Entity _entity)
    {}

    template<typename T>
    void Scene::on_component_added(Entity _entity, T& _component)
    {
        EXW_LOG_WARNING("Scene::on_component_added() is not implemented");
        static_assert(false);
    }

    template <>
    void Scene::on_component_added<TagComponent>(Entity _entity, TagComponent& _component)
    {}

    template <>
    void Scene::on_component_added<TransformComponent>(Entity _entity, TransformComponent& _component)
    {}

    template <>
    void Scene::on_component_added<SpriteRendererComponent>(Entity _entity, SpriteRendererComponent& _component)
    {}

    template <>
    void Scene::on_component_added<CameraComponent>(Entity _entity, CameraComponent& _component)
    {
        _component.Camera.set_viewport_size(m_Viewport_width, m_Viewport_height);
    }
}
