#shader vertex
#version 430

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 in_color;

uniform vec3 u_rotation;

out vec3 v_color;

mat3 Xrotation(float rad)
{
	mat3 xrot = mat3(
		1.0f, 0.0f, 0.0f,
		0.0f, cos(rad), -sin(rad),
		0.0f, sin(rad), cos(rad)
	);

	return xrot;
}

mat3 Yrotation(float rad)
{
	mat3 yrot = mat3(
		cos(rad), 0.0f, sin(rad),
		    0.0f, 1.0f,     0.0f,
	   -sin(rad), 0.0f, cos(rad)
	);

	return yrot;
}

mat3 Zrotation(float rad)
{
	mat3 zrot = mat3(
		cos(rad), -sin(rad), 0.0f,
		cos(rad),  sin(rad), 0.0f,
		    0.0f,      0.0f, 1.0f
	);

	return zrot;
}


void main()
{
	vec3 new_pos = (Xrotation(u_rotation.x) * Yrotation(u_rotation.y) * Zrotation(u_rotation.z)) * pos;

	gl_Position = vec4(new_pos.x , new_pos.y, new_pos.z, 1.0f);
	v_color = in_color;
}

#shader fragment
#version 430

in vec3 v_color;

out vec4 color;

void main()
{
	color = vec4(v_color, 1.0f);
}