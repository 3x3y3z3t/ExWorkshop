// ;
#include "expch.h"
#include "SceneSerializer.h"

#include "Entity.h"
#include "Component.h"

#include "exw\maths\vector2.h"
#include "exw\maths\vector3.h"
#include "exw\maths\vector4.h"

#include <yaml-cpp\yaml.h>

#pragma region Helper Struct
namespace YAML
{
    template <>
    struct convert<exw::maths::vector2>
    {
        static Node encode(const exw::maths::vector2& _vector)
        {
            Node node;
            node.push_back(_vector.x);
            node.push_back(_vector.y);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& _node, exw::maths::vector3& _vector)
        {
            if (!_node.IsSequence() || _node.size() != 2Ui64)
            {
                return false;
            }

            _vector.x = _node[0].as<float>();
            _vector.y = _node[1].as<float>();
            return true;
        }
    };

    template <>
    struct convert<exw::maths::vector3>
    {
        static Node encode(const exw::maths::vector3& _vector)
        {
            Node node;
            node.push_back(_vector.x);
            node.push_back(_vector.y);
            node.push_back(_vector.z);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& _node, exw::maths::vector3& _vector)
        {
            if (!_node.IsSequence() || _node.size() != 3Ui64)
            {
                return false;
            }

            _vector.x = _node[0].as<float>();
            _vector.y = _node[1].as<float>();
            _vector.z = _node[2].as<float>();
            return true;
        }
    };

    template <>
    struct convert<exw::maths::vector4>
    {
        static Node encode(const exw::maths::vector4& _vector)
        {
            Node node;
            node.push_back(_vector.x);
            node.push_back(_vector.y);
            node.push_back(_vector.z);
            node.push_back(_vector.w);
            node.SetStyle(EmitterStyle::Flow);
            return node;
        }

        static bool decode(const Node& _node, exw::maths::vector4& _vector)
        {
            if (!_node.IsSequence() || _node.size() != 4Ui64)
            {
                return false;
            }

            _vector.x = _node[0].as<float>();
            _vector.y = _node[1].as<float>();
            _vector.z = _node[2].as<float>();
            _vector.w = _node[3].as<float>();
            return true;
        }
    };
}
#pragma endregion

namespace exw
{
    #pragma region Helper Functions
    YAML::Emitter& operator<<(YAML::Emitter& _out, const maths::vector2& _vector)
    {
        _out << YAML::Flow;
        _out << YAML::BeginSeq << _vector.x << _vector.y << YAML::EndSeq;
        return _out;
    }

    YAML::Emitter& operator<<(YAML::Emitter& _out, const maths::vector3& _vector)
    {
        _out << YAML::Flow;
        _out << YAML::BeginSeq << _vector.x << _vector.y << _vector.z << YAML::EndSeq;
        return _out;
    }

    YAML::Emitter& operator<<(YAML::Emitter& _out, const maths::vector4& _vector)
    {
        _out << YAML::Flow;
        _out << YAML::BeginSeq << _vector.x << _vector.y << _vector.z << _vector.w << YAML::EndSeq;
        return _out;
    }

    static void serialize_entity(YAML::Emitter& _emitter, const Entity& _entity)
    {
        _emitter << YAML::BeginMap;
        _emitter << YAML::Key << "Entity" << YAML::Value << _entity.get_id();

        if (_entity.has_component<TagComponent>())
        {
            auto& component = _entity.get_component<TagComponent>().Tag;

            _emitter << YAML::Key << "TagComponent";
            _emitter << YAML::BeginMap;
            {
                _emitter << YAML::Key << "Tag" << YAML::Value << component;
            }
            _emitter << YAML::EndMap;
        }

        if (_entity.has_component<TransformComponent>())
        {
            auto& component = _entity.get_component<TransformComponent>();

            _emitter << YAML::Key << "TransformComponent";
            _emitter << YAML::BeginMap;
            {
                _emitter << YAML::Key << "Translation" << YAML::Value << component.Translation;
                _emitter << YAML::Key << "Rotation" << YAML::Value << component.Rotation;
                _emitter << YAML::Key << "Scale" << YAML::Value << component.Scale;
            }
            _emitter << YAML::EndMap;
        }

        if (_entity.has_component<CameraComponent>())
        {
            auto& component = _entity.get_component<CameraComponent>();
            auto& camera = component.Camera;

            _emitter << YAML::Key << "CameraComponent";
            _emitter << YAML::BeginMap;
            {
                _emitter << YAML::Key << "Camera" << YAML::Value;
                _emitter << YAML::BeginMap;
                {
                    _emitter << YAML::Key << "ProjectionType" << YAML::Value << (int)camera.get_projection_type();

                    _emitter << YAML::Key << "PerspectiveFOV" << YAML::Value << (int)camera.get_perspective_vertical_fov();
                    _emitter << YAML::Key << "PerspectiveNear" << YAML::Value << (int)camera.get_perspective_near_clip();
                    _emitter << YAML::Key << "PerspectiveFar" << YAML::Value << (int)camera.get_perspective_far_clip();

                    _emitter << YAML::Key << "OrthographicSize" << YAML::Value << (int)camera.get_orthographic_size();
                    _emitter << YAML::Key << "OrthographicNear" << YAML::Value << (int)camera.get_orthographic_near_clip();
                    _emitter << YAML::Key << "OrthographicFar" << YAML::Value << (int)camera.get_orthographic_far_clip();
                }
                _emitter << YAML::EndMap;

                _emitter << YAML::Key << "IsPrimary" << YAML::Value << component.IsPrimary;
                _emitter << YAML::Key << "IsFixedAspectRatio" << YAML::Value << component.IsFixedAspectRatio;
            }
            _emitter << YAML::EndMap;
        }

        if (_entity.has_component<SpriteRendererComponent>())
        {
            auto& component = _entity.get_component<SpriteRendererComponent>();

            _emitter << YAML::Key << "SpriteRendererComponent";
            _emitter << YAML::BeginMap;
            {
                _emitter << YAML::Key << "Color" << YAML::Value << component.Color;
            }
            _emitter << YAML::EndMap;
        }

        _emitter << YAML::EndMap;
    }

    #pragma endregion

    SceneSerializer::SceneSerializer(const refs::ref<Scene>& _scene)
        : m_Scene(_scene)
    {}

    bool SceneSerializer::serialize(const std::string& _filepath)
    {
        YAML::Emitter emitter;
        emitter << YAML::BeginMap;
        emitter << YAML::Key << "Scene" << YAML::Value << "Untitled";
        emitter << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
        m_Scene->m_Registry.each([&] (auto _entityId)
        {
            Entity entity = { _entityId, m_Scene.get() };
            if (!entity)
                return;

            serialize_entity(emitter, entity);
        });
        emitter << YAML::EndSeq;
        emitter << YAML::EndMap;

        std::ofstream fout(_filepath);
        fout << emitter.c_str();
        return true;
    }

    bool SceneSerializer::deserialize(const std::string& _filepath)
    {
        YAML::Node data = YAML::LoadFile(_filepath);
        if (!data["Scene"])
        {
            EXW_LOG_WARNING("Invalid scene in '{0}'.", _filepath);
            return false;
        }

        std::string sceneName = data["Scene"].as<std::string>();
        EXW_LOG_TRACE("Deserializing scene '{0}'...", sceneName);
        auto entities = data["Entities"];
        if (entities)
        {
            for (auto entity : entities)
            {
                uint64_t uuid = entity["Entity"].as<uint64_t>();

                std::string name;
                {
                    auto component = entity["TagComponent"];
                    if (component)
                    {
                        name = component["Tag"].as<std::string>();
                    }
                }
                EXW_LOG_TRACE("Deserialized entity {0} > {1}", uuid, name);

                Entity deserializedEntity = m_Scene->create_entity(name);

                {
                    auto component = entity["TransformComponent"];
                    if (component)
                    {
                        auto& transform = deserializedEntity.get_component<TransformComponent>();
                        transform.Translation = component["Translation"].as<maths::vector3>();
                        transform.Rotation = component["Rotation"].as<maths::vector3>();
                        transform.Scale = component["Scale"].as<maths::vector3>();
                    }
                }
                {
                    auto component = entity["CameraComponent"];
                    if (component)
                    {
                        auto& camera = deserializedEntity.add_component<CameraComponent>();
                        auto& cameraProps = component["Camera"];
                        camera.Camera.set_projection_type((SceneCamera::ProjectionType)cameraProps["ProjectionType"].as<int>());

                        camera.Camera.set_perspective_vertical_fov(cameraProps["PerspectiveFOV"].as<float>());
                        camera.Camera.set_perspective_near_clip(cameraProps["PerspectiveNear"].as<float>());
                        camera.Camera.set_perspective_far_clip(cameraProps["PerspectiveFar"].as<float>());

                        camera.Camera.set_orthographic_size(cameraProps["OrthographicSize"].as<float>());
                        camera.Camera.set_orthographic_near_clip(cameraProps["OrthographicNear"].as<float>());
                        camera.Camera.set_orthographic_far_clip(cameraProps["OrthographicFar"].as<float>());

                        camera.IsPrimary = component["IsPrimary"].as<bool>();
                        camera.IsFixedAspectRatio = component["IsFixedAspectRatio"].as<bool>();
                    }
                }
                {
                    auto component = entity["SpriteRendererComponent"];
                    if (component)
                    {
                        auto& sprite = deserializedEntity.add_component<SpriteRendererComponent>();

                        sprite.Color = component["Color"].as<maths::vector4>();
                    }
                }
            }
        }

        return true;
    }
}
