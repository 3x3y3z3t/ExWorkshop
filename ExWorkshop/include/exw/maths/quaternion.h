// ;
#pragma once
#ifdef EXW_ENABLE_EXPERIMENTAL
    #ifndef GLM_ENABLE_EXPERIMENTAL
        #define GLM_ENABLE_EXPERIMENTAL
    #endif
    #include <glm\gtx\quaternion.hpp>
#else
    #include <glm\gtc\quaternion.hpp>
#endif

namespace exw
{
    namespace maths
    {
        struct vector3;
        struct matrix4;

        struct quaternion
        {
            union
            {
                glm::quat raw;
            };

            quaternion();
            quaternion(const maths::vector3& _vct);


            matrix4 to_matrix4() const;
        };
    }
}

#include "quaternion.inl"
