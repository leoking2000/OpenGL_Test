#shader vertex
#version 430

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 tex_cord;
layout(location = 2) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform vec3 u_light_pos;

out vec2 v_tex_cord;
out vec3 v_normal;
out vec3 v_world_pos;
out vec3 v_light_pos;

void main()
{
    mat4 view_model = view * model;

	gl_Position = proj * view_model * vec4(pos, 1.0);

	v_tex_cord  = tex_cord;
	v_normal    = vec3( ( view_model * vec4(     normal, 0.0) ).xyz );
	v_world_pos = vec3( ( view_model * vec4(        pos, 1.0) ).xyz );
    v_light_pos = vec3( ( view       * vec4(u_light_pos, 1.0) ).xyz );
}

#shader fragment
#version 430

in vec2 v_tex_cord;
in vec3 v_normal;
in vec3 v_world_pos;
in vec3 v_light_pos;

uniform sampler2D u_Tex;
uniform vec3 u_light_color;

uniform float ambientStrength;
uniform float specularStrength;
uniform float shininess;

out vec4 color;

void main()
{
    vec3 ambient = ambientStrength * u_light_color;

    vec3 surf_normal = normalize(v_normal);
    vec3 lightDir = normalize(v_world_pos - v_light_pos);
    vec3 diffuse = max(dot(surf_normal, -lightDir), 0.0) * u_light_color;

	vec3 tex_color = vec3(texture(u_Tex, v_tex_cord).xyz);

    vec3 viewDir = normalize(-v_world_pos);
    vec3 reflectDir = reflect(lightDir, surf_normal);
    vec3 specular = specularStrength * pow(max(dot(viewDir, reflectDir), 0.0), shininess) * u_light_color;

    vec3 result = (ambient + diffuse + specular) * tex_color;
	color = vec4(result, 1.0);
}