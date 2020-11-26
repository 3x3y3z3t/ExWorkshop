// ;
#pragma once

namespace exw
{
    namespace MouseButtons
    {
        using ButtonCode = uint8_t;

        enum : ButtonCode
        {
            Btn_1 = 0,
            Btn_2 = 1,
            Btn_3 = 2,
            Btn_4 = 3,
            Btn_5 = 4,
            Btn_6 = 5,
            Btn_7 = 6,
            Btn_8 = 7,

            Btn_Left = Btn_1,
            Btn_Right = Btn_2,
            Btn_Middle = Btn_3,

            Btn_Last_btn = Btn_8,
        };

        //inline std::ostream& operator<<(std::ostream& _os, MouseButtons _button)
        //{
        //    _os << static_cast<int32_t>(_button);
        //    return _os;
        //}
    }
}
