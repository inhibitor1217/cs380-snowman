#version 330 core

in vec4 fragmentPosition;
in vec4 frag_color;
in vec4 fragmentNormal;
out vec4 output_color;

uniform float enable_lighting;

void main()
{
	const float ambient = 0.1;

	if (enable_lighting > 0.5)
	{
		vec3 tolight = normalize(vec3(10.0f) - fragmentPosition.xyz);
		vec3 normal = normalize(fragmentNormal.xyz);

		float diffuse = max(ambient, dot(normal, tolight));
		output_color = frag_color * diffuse;
	}
	else
	{
		output_color = frag_color;
	}
}