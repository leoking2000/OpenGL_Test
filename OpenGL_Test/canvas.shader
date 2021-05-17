#shader vertex
#version 330 core

layout(location = 0) in vec4 pos;
layout(location = 1) in vec2 tex_cord;

out vec2 v_tex_cord;

void main()
{
     gl_Position = pos;
     v_tex_cord = tex_cord;
}

#shader fragment
#version 330 core

in vec2 v_tex_cord;
out vec4 color;

uniform sampler2D u_Tex;

void main()
{
    vec4 Tex_color = texture(u_Tex, v_tex_cord);
    color = Tex_color;
}
