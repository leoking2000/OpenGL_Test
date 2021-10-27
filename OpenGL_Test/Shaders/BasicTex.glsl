#shader vertex
#version 330

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
#version 330
struct Material 
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

in vec2 v_tex_cord;
in vec3 v_normal;
in vec3 v_world_pos;
in vec3 v_light_pos;

uniform vec3 u_light_color;
uniform Material mat;

uniform sampler2D texture_diffuse;

out vec4 color;

void main()
{
    vec3 ambient = mat.ambient * u_light_color;

    vec3 surf_normal = normalize(v_normal);
    vec3 lightDir = normalize(v_light_pos - v_world_pos);
    float diff = max(0.0, dot(surf_normal, lightDir));
    vec3 diffuse = (diff * mat.diffuse) * u_light_color;

    vec3 viewDir = normalize(-v_world_pos);
    vec3 reflectDir = reflect(-lightDir, surf_normal);
    float spec = pow( max(0.0, dot(viewDir, reflectDir)), mat.shininess);
    vec3 specular = (spec * mat.specular)  * u_light_color;

    vec3 tex_color = vec3(texture(texture_diffuse, v_tex_cord).xyz);
    vec3 result = (ambient + diffuse + specular) * tex_color;
	color = vec4(result, 1.0);
}