#pragma once
#include "math.h"


namespace graphics
{
	class Transform
	{
	public:
		glm::vec3 pos;
		glm::vec3 rot;
	public:
		void RotateZ(float rad);
		void RotateX(float rad);
		void RotateY(float rad);

		void Translate(const glm::vec3& offset);

        template<class V>
        static void TransformVertex(V& ver, const Transform& transform)
        {
            float sin = std::sinf(transform.rot.z);
            float cos = std::cosf(transform.rot.z);
            float rZ[9] = { cos, -sin, 0.0f,
                            sin,  cos, 0.0f,
                           0.0f, 0.0f, 1.0f };

            sin = std::sinf(transform.rot.x);
            cos = std::cosf(transform.rot.x);
            float rX[9] = { 1.0f, 0.0f, 0.0f,
                            0.0f, cos,  -sin,
                            0.0f, sin,   cos };

            sin = std::sinf(transform.rot.y);
            cos = std::cosf(transform.rot.y);
            float rY[9] = { cos, 0.0f,  sin,
                           0.0f, 1.0f, 0.0f,
                           -sin, 0.0f,  cos };

            glm::mat3x3 rotation = glm::make_mat3x3(rZ) * glm::make_mat3x3(rX) * glm::make_mat3x3(rY);
              

            ver *= rotation;
            ver.pos += transform.pos;
        }
	};
}
