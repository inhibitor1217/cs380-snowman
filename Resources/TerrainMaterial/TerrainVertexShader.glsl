#version 330 core

layout(location = 0) in vec4 pos;
layout(location = 1) in vec4 color;
layout(location = 2) in vec4 normal;

uniform vec4 global_color;
uniform mat4 worldTransform;
uniform mat4 cameraTransform;
uniform mat4 projectionMatrix;

out vec4 frag_color;
out vec3 out_normal;
out vec3 toCamera;
out float transparency;

const float terrain_inner_radius = 0.5;
const float terrain_outer_radius = 0.8;

mat4 NormalMatrix(mat4 MVM)
{
	mat4 invm = inverse(MVM);
	invm[0][3] = 0;
	invm[1][3] = 0;
	invm[2][3] = 0;

	return transpose(invm);
}

void main()
{
	vec4 world_pos = worldTransform * pos;

	// Output position of the vertex, in clip space : MVP * position
	mat4 MVM = inverse(cameraTransform) * worldTransform;
	mat4 NVM = NormalMatrix(MVM);

	vec4 wPosition = MVM * pos;
	gl_Position = projectionMatrix * wPosition;

	out_normal = normalize(vec3(worldTransform * normal));
	toCamera = cameraTransform[3].xyz - vec3(world_pos);

	float radius = length(pos.xy);
	transparency = 1.0 - clamp((radius - terrain_inner_radius) / (terrain_outer_radius - terrain_inner_radius), 0.0f, 1.0f);

    frag_color = color.x * global_color;
}