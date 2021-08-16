#shader vertex
#version 330

layout(location = 0) in vec3 pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	gl_Position = proj * view * model * vec4(pos, 1.0);
}

#shader fragment
#version 330

uniform vec3 matColor;
out vec4 color;

void main()
{
	color = vec4(matColor, 1.0);
}