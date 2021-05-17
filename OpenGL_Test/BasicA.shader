#shader vertex
#version 330 core

layout(location = 0) in vec4 pos;
layout(location = 1) in vec4 col;
out vec4 v_color_out;

uniform vec4 u_offset;

void main()
{
     gl_Position = pos + u_offset;
     v_color_out = col;
}

#shader fragment
#version 330 core

in vec4 v_color_out;
out vec4 color;

uniform vec4 u_color;

void main()
{
    color = v_color_out + u_color;
}
