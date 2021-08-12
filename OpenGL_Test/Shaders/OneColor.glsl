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

struct Material 
{
    vec3 color;
};

uniform Material mat;

out vec4 color;

void main()
{
	color = vec4(mat.color, 1.0);
}