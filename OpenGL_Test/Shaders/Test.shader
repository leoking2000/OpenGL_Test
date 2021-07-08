#shader vertex
#version 430

layout(location = 0) in vec2 pos;
layout(location = 1) in vec3 in_color;
layout(location = 2) in vec2 tex_cord;

uniform vec2 u_offset;

out vec3 v_color;
out vec2 v_tex_cord;

void main()
{
	gl_Position = vec4(pos.x + u_offset.x, pos.y + u_offset.y, 0.0f, 1.0);
	v_color = in_color;
	v_tex_cord = tex_cord;
}

#shader fragment
#version 430

in vec3 v_color;
in vec2 v_tex_cord;

uniform sampler2D u_Tex;

out vec4 color;

void main()
{
	vec4 Tex_color = texture(u_Tex, v_tex_cord);
	color = vec4(v_color, 1.0f) * Tex_color;
}

