#shader vertex
#version 330

layout(location = 0) in vec3 pos;
uniform mat4 MVPshadow;

void main()
{
	gl_Position = MVPshadow * vec4(pos, 1.0);
}

#shader fragment
#version 330
void main()
{
}