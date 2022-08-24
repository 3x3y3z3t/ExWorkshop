/*  Input.h
*   Version: 1.1 (2022.07.22)
*
*   Contributor
*       Arime-chan
*/
#pragma once
#include "exwpch.h"

#include "exw\events\KeyCodes.h"
#include "exw\maths\Maths.h"

namespace exw
{
    class Input
    {
    public:
        static bool is_key_pressed(Keys::KeyCode _key);
        static bool is_mouse_btn_pressed(MouseBtn::MouseBtnCode _btn);

        static maths::vector2 get_cursor_pos();
        static float get_cursor_pos_x() { return get_cursor_pos().x; }
        static float get_cursor_pos_y() { return get_cursor_pos().y; }
    };
}