#version 330 core

in vec4 fragmentPosition;
in vec4 frag_color;
in vec4 fragmentNormal;
out vec4 output_color;

void main()
{
	const float ambient = 0.1;

	vec3 tolight = normalize(vec3(10.0f) - fragmentPosition.xyz);
	vec3 normal = normalize(fragmentNormal.xyz);

	float diffuse = max(ambient, dot(normal, tolight));
	vec4 intensity = frag_color * diffuse;

	output_color = intensity;
}