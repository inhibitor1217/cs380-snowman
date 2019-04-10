#version 330 core

in vec4 frag_color;
in vec3 out_normal;
in vec3 toCamera;
in float transparency;

out vec4 output_color;

void main()
{
	const float ambient = 0.1;
	const vec4 light_color = vec4(1.0f, 1.0f, 1.0f, 1.0f);

	const vec3 tolight = vec3(0.0f, 0.0f, 1.0f);
	vec3 tocamera = normalize(toCamera);
	vec3 reflectedlight = normalize(reflect(-tolight, out_normal));
	float specular = max(dot(reflectedlight, tocamera), 0.0);
	specular = pow(specular, 8);

	float diffuse = max(ambient, dot(out_normal, tolight));
	vec4 color = frag_color * diffuse + specular * light_color;
	output_color = vec4(color.xyz, transparency);
}