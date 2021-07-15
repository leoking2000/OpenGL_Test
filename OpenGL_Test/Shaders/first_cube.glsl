#shader vertex
#version 330

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 in_color;

uniform vec3 u_rotation;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 v_color;

// builds and returns a matrix that performs a rotation around the X axis
mat4 RotateX(float rad)
{
	mat4 xrot = mat4(1.0, 0.0, 0.0, 0.0,
		0.0, cos(rad), -sin(rad), 0.0,
		0.0, sin(rad), cos(rad), 0.0,
		0.0, 0.0, 0.0, 1.0);
	return xrot;
}
// builds and returns a matrix that performs a rotation around the Y axis
mat4 RotateY(float rad)
{
	mat4 yrot = mat4(cos(rad), 0.0, sin(rad), 0.0,
		0.0, 1.0, 0.0, 0.0,
		-sin(rad), 0.0, cos(rad), 0.0,
		0.0, 0.0, 0.0, 1.0);
	return yrot;
}
// builds and returns a matrix that performs a rotation around the Z axis
mat4 RotateZ(float rad)
{
	mat4 zrot = mat4(cos(rad), -sin(rad), 0.0, 0.0,
		sin(rad), cos(rad), 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0);
	return zrot;
}

void main()
{
	vec4 world_pos = model * RotateX(u_rotation.x) * RotateY(u_rotation.y) * RotateZ(u_rotation.z) * vec4(pos, 1.0f);

	gl_Position = proj * view * world_pos;
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