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

        const maths::matrix4& get_transform()
        {
            bool isDirty = false;

            if (Translation != m_Transform[3])
            {
                isDirty = true;
            }
            if (Rotation != m_Rotation_previous)
            {
                isDirty = true;
                m_Rotation_previous = Rotation;
            }
            if (Scale != m_Scale_previous)
            {
                isDirty = true;
                m_Scale_previous = Scale;
            }

            if (isDirty)
            {
                //EXW_LOG_TRACE("Component is dirty, recalculating Transformation matrix...");
                // recalculate transformation matrix;
                m_Transform = maths::translate(maths::matrix4(1.0f), Translation)
                    * maths::rotate(maths::matrix4(1.0f), ((maths::vector3)Rotation).x, { 1.0f, 0.0f, 0.0f })
                    * maths::rotate(maths::matrix4(1.0f), ((maths::vector3)Rotation).y, { 0.0f, 1.0f, 0.0f })
                    * maths::rotate(maths::matrix4(1.0f), ((maths::vector3)Rotation).z, { 0.0f, 0.0f, 1.0f })
                    * maths::scale(maths::matrix4(1.0f), Scale);
            }

            return m_Transform;
        }

        private:
            maths::vector3 m_Rotation_previous = { 0.0f, 0.0f, 0.0f };
            maths::vector3 m_Scale_previous = { 0.0f, 0.0f, 0.0f };
            maths::matrix4 m_Transform = maths::matrix4();
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
