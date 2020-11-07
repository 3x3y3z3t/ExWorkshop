// 
#pragma once
#include "expch.h"

#include "ScriptableEntity.h"

#include "exw\camera\SceneCamera.h"

#include "exw\maths\matrix4.h"
#include "exw\maths\vector2.h"
#include "exw\maths\vector3.h"
#include "exw\maths\vector4.h"

namespace exw
{
    struct TagComponent
    {
        std::string Tag;

        TagComponent() = default;
        TagComponent(const TagComponent& _component) = default;
        TagComponent(const std::string& _tag) : Tag(_tag) {}
    };

    struct TransformComponent
    {
        maths::vector3 Translation = { 0.0f, 0.0f, 0.0f };
        maths::vector3 Rotation = { 0.0f, 0.0f, 0.0f };
        maths::vector3 Scale = { 1.0f, 1.0f, 1.0f };

        TransformComponent() = default;
        TransformComponent(const TransformComponent& _component) = default;
        TransformComponent(const maths::vector3& _translation) : Translation(_translation) {}

        maths::matrix4 get_transform() const
        {
            maths::matrix4 rotation = maths::rotate(maths::matrix4(1.0f), Rotation.x, { 1.0f, 0.0f, 0.0f })
                * maths::rotate(maths::matrix4(1.0f), Rotation.y, { 0.0f, 1.0f, 0.0f })
                * maths::rotate(maths::matrix4(1.0f), Rotation.z, { 0.0f, 0.0f, 1.0f });
            return maths::translate(maths::matrix4(1.0f), Translation)
                * rotation
                * maths::scale(maths::matrix4(1.0f), Scale);
        }
    };

    struct SpriteRendererComponent
    {
        maths::vector4 Color = { 1.0f, 1.0f, 1.0f, 1.0f };

        SpriteRendererComponent() = default;
        SpriteRendererComponent(const SpriteRendererComponent& _component) = default;
        SpriteRendererComponent(const maths::vector4& _color) : Color(_color) {}
    };

    struct CameraComponent
    {
        SceneCamera Camera;
        bool IsPrimary = false;
        bool IsFixedAspectRatio = false;

        CameraComponent() = default;
        CameraComponent(const CameraComponent& _component) = default;
        CameraComponent(bool _isPrimary) : IsPrimary(_isPrimary) {}
    };

    struct ScriptComponent
    {
        ScriptableEntity* Instance = nullptr;

        ScriptableEntity*(*instantiate_script)();
        void(*destroy_script)(ScriptComponent*);

        template <typename T>
        void bind()
        {
            instantiate_script = [] () { return static_cast<ScriptableEntity*>(new T()); };
            destroy_script = [] (ScriptComponent* _component) { delete _component->Instance; _component->Instance = nullptr; };
        }
    };

    struct NativeScriptComponent : public ScriptComponent
    {};
}
