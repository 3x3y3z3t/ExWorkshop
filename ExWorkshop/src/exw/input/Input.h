// ;
#pragma once

#include "exw\Common.h"

#include "KeyCodes.h"
#include "MouseButtonCodes.h"

namespace exw
{
    struct vec2
    {
        float x;
        float y;
    };

    /* Hold the name for an input to be mapped. */
    using InputName = uint16_t;
    enum : InputName
    {
        CameraMoveLeft = 1,
        CameraMoveRight = 2,
        CameraMoveUp = 3,
        CameraMoveDown = 4,
        CameraRotateClockwise = 5,
        CameraRotateAntiClockwise = 6,
    };

    struct InputKey
    {
        std::variant<Keys::KeyCode, MouseButtons::ButtonCode> value;

        InputKey() = default;
        InputKey(Keys::KeyCode _key) { value = _key; }
        InputKey(MouseButtons::ButtonCode _button) { value = _button; }
    };

    class Input
    {
    public:
        static bool is_key_pressed(Keys::KeyCode _key);
        static bool is_mouse_button_pressed(MouseButtons::ButtonCode _button);

        static vec2 get_cursor_position();
        static float get_cursor_pos_x();
        static float get_cursor_pos_y();

        template <typename T>
        static void remap(T _name, InputKey _input) { s_Mapping[static_cast<InputName>(_name)] = _input; }
        static void remap(InputName _name, InputKey _input) { s_Mapping[_name] = _input; }

        static bool is_input_pressed(InputName _name)
        {
            if (s_Mapping.count(_name) != 0)
                return is_input_pressed(s_Mapping[_name]);

            EXW_LOG_WARNING("The input {0} is not mapped.", _name);
            return false;
        }

        static bool is_input_pressed(InputKey _input)
        {
            if (std::holds_alternative<Keys::KeyCode>(_input.value))
                return is_key_pressed(std::get<Keys::KeyCode>(_input.value));

            if (std::holds_alternative<MouseButtons::ButtonCode>(_input.value))
                return is_mouse_button_pressed(std::get<MouseButtons::ButtonCode>(_input.value));

            // control should never fall down here;
            EXW_LOG_WARNING("Unknown Input type!");
            return false;
        }

    private:
        static std::unordered_map<uint16_t, InputKey> s_Mapping;
    };
}
