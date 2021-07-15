#shader vertex
#version 330

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
	v_normal    = vec3( (model * vec4(normal, 0.0)).xyz );
	v_world_pos = vec3(world_pos.xyz);
}

#shader fragment
#version 430

in vec2 v_tex_cord;
in vec3 v_normal;
in vec3 v_world_pos;

uniform sampler2D u_Tex;
uniform vec3 u_light_dir;

// specular
float specular_power = 30.0;
float specular_intensity = 0.1;

out vec4 color;

void main()
{
	vec3 diffuse = vec3(1.0, 1.0, 1.0);
	vec3 ambient = vec3(0.1, 0.1, 0.1);

	vec3 surf_normal = normalize(v_normal);

	vec3 tex_color = vec3(texture(u_Tex, v_tex_cord).xyz);

	vec3 light = diffuse * max(0.0, dot(-u_light_dir, surf_normal));

	//vec3 reflection = reflect(-u_light_dir, surf_normal);

	//vec3 specular = diffuse * specular_intensity * pow(max(0.0, dot(-reflection, normalize(v_world_pos))), specular_intensity);
	vec3 specular = vec3(0.0, 0.0, 0.0);

	light.x = clamp(light.x + specular.x + ambient.x, 0.0, 1.0);
	light.y = clamp(light.y + specular.y + ambient.y, 0.0, 1.0);
	light.z = clamp(light.z + specular.z + ambient.z, 0.0, 1.0);

	
	tex_color.x = clamp(light.x * tex_color.x, 0.0, 1.0);
	tex_color.y = clamp(light.y * tex_color.y, 0.0, 1.0);
	tex_color.z = clamp(light.z * tex_color.z, 0.0, 1.0);


	color = vec4(tex_color, 1.0);

}