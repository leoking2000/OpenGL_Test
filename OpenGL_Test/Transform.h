#pragma once
#include "math.h"


namespace graphics
{
	class Transform
	{
	public:
		Math::vec3 pos;
		Math::vec3 rot;
        float scale = 1.0f;
	public:
		void RotateZ(float rad);
		void RotateX(float rad);
		void RotateY(float rad);

		void Translate(const Math::vec3& offset);

        template<class V>
        static void TransformVertex(V& ver, const Transform& transform)
        {
            Math::mat3 rotation_scale = Math::mat3::rotationX(transform.rot.x) * 
								        Math::mat3::rotationY(transform.rot.y) * 
								        Math::mat3::rotationZ(transform.rot.z) *
										Math::mat3::scale(transform.scale);
              
            ver *= rotation_scale;
            ver += transform.pos;
        }
	};
}
