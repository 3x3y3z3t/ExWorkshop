// ;
#pragma once

namespace exw
{
    class Timestep
    {
    public:
        Timestep(float _time = 0.0f)
            : m_Time(_time)
        {}

        friend Timestep operator -(const Timestep& _ts1, const Timestep& _ts2) { return Timestep(_ts1.m_Time - _ts2.m_Time); }
        const Timestep& operator -=(const Timestep& _ts) { m_Time -= _ts; return *this; }
        operator float() const { return m_Time; }

    public:
        float seconds() const { return m_Time * 0.001f; }
        float milliseconds() const { return m_Time; }

    private:
        float m_Time; // in milliseconds.
    };
}
