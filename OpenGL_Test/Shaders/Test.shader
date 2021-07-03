#shader vertex
#version 430

layout(location = 0) in vec2 pos;

uniform float u_offset;

void main()
{
	gl_Position = vec4(pos.x, pos.y + u_offset, 0.0, 1.0);
}

#shader fragment
#version 430

out vec4 color; 

void main()
{
	color = vec4(1.0, 0.0, 0.0, 1.0);
}

