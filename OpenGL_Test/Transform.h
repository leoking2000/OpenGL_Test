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
            Math::mat4 T = Math::mat4::rotationX(transform.rot.x) * 
						   Math::mat4::rotationY(transform.rot.y) * 
						   Math::mat4::rotationZ(transform.rot.z) *
						   Math::mat4::scale(transform.scale) *
						   Math::mat4::Translation3D(transform.pos.x, transform.pos.y, transform.pos.z);
              
            ver *= T;
        }
	};
}
