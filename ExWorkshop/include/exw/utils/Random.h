// ;
#pragma once

#include "exw\Common.h"

namespace exw
{
    namespace utils
    {
        class RNG32
        {
        private:
            static std::mt19937 s_Engine;

        public:
            inline static void init(uint32_t _seed = 0U)
            {
                if (_seed == 0U)
                    _seed = std::random_device()();
                s_Engine.seed(_seed);
            }

            template <typename T = int>
            inline static T next_int(T _lower = 0, T _upper = std::numeric_limits<T>::max())
            {
                if (_lower > _upper)
                    return 0;
                return std::uniform_int_distribution<T>(_lower, _upper)(s_Engine);
            }

            template <typename T = float>
            inline static T next_float(T _lower = (T)0, T _upper = (T)1)
            {
                if (_lower > _upper)
                    return 0.0f;
                return std::uniform_real_distribution<T>(_lower, _upper)(s_Engine);
            }
        };
    }
}
