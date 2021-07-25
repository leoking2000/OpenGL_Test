#shader vertex
#version 430

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 tex_cord;
layout(location = 2) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec2 v_tex_cord;
out vec3 v_normal;
out vec3 v_world_pos;

void main()
{
	vec4 world_pos = model * vec4(pos, 1.0);

	gl_Position = proj * view * world_pos;

	v_tex_cord  = tex_cord;
	v_normal    = vec3( ( model * vec4(normal, 0.0) ).xyz );
	v_world_pos = vec3(world_pos.xyz);
}

#shader fragment
#version 430

in vec2 v_tex_cord;
in vec3 v_normal;
in vec3 v_world_pos;

uniform sampler2D u_Tex;

uniform vec3 u_light_color;
uniform vec3 u_light_pos;

uniform vec3 u_cameraPos;

out vec4 color;

float specularStrength = 0.5;
float specularPower = 32;

float ambientStrength = 0.1;

void main()
{

    vec3 ambient = ambientStrength * u_light_color;

    vec3 surf_normal = normalize(v_normal);
    vec3 lightDir = normalize(v_world_pos - u_light_pos);
    vec3 diffuse = max(dot(surf_normal, -lightDir), 0.0) * u_light_color;

	vec3 tex_color = vec3(texture(u_Tex, v_tex_cord).xyz);

    vec3 viewDir = normalize(u_cameraPos - v_world_pos);
    vec3 reflectDir = reflect(lightDir, surf_normal);
    vec3 specular = specularStrength * pow(max(dot(viewDir, reflectDir), 0.0), specularPower) * u_light_color;

    vec3 result = (ambient + diffuse + specular) * tex_color;
	color = vec4(result, 1.0);
}