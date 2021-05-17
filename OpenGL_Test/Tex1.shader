#shader vertex
#version 330 core

layout(location = 0) in vec4 pos;
layout(location = 1) in vec4 col;
layout(location = 2) in vec2 tex_cord;

out vec4 v_color_out;
out vec2 v_tex_cord;

uniform vec4 u_offset;

void main()
{
     gl_Position = pos + u_offset;
     v_color_out = col;
     v_tex_cord = tex_cord;
}

#shader fragment
#version 330 core

in vec4 v_color_out;
in vec2 v_tex_cord;

out vec4 color;

uniform sampler2D u_Tex;

void main()
{
    vec4 Tex_color = texture(u_Tex, v_tex_cord);
    color = Tex_color;
}
