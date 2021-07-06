#shader vertex
#version 430

layout(location = 0) in vec2 pos;
layout(location = 1) in vec3 in_color;

uniform vec2 u_offset;

out vec3 v_color;

void main()
{
	gl_Position = vec4(pos.x + u_offset.x, pos.y + u_offset.y, 0.0, 1.0);
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

