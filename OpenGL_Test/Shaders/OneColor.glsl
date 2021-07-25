#shader vertex
#version 430

layout(location = 0) in vec3 pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	gl_Position = proj * view * model * vec4(pos, 1.0);
}

#shader fragment
#version 430

uniform vec3 u_object_color;

out vec4 color;

void main()
{
	color = vec4(u_object_color, 1.0);
}