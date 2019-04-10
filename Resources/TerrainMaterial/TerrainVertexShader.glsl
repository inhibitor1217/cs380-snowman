#version 330 core

layout(location = 0) in vec4 pos;
layout(location = 1) in vec4 color;
layout(location = 2) in vec4 normal;

uniform mat4 worldTransform;
uniform mat4 cameraTransform;
uniform mat4 projectionMatrix;

out vec4 frag_color;
out vec3 out_normal;
out vec3 toCamera;

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
	// Output position of the vertex, in clip space : MVP * position
	mat4 MVM = inverse(cameraTransform) * worldTransform;
	mat4 NVM = NormalMatrix(MVM);

	vec4 wPosition = MVM * pos;
	gl_Position = projectionMatrix * wPosition;

	out_normal = normalize(vec3(worldTransform * normal));
	toCamera = cameraTransform[3].xyz - vec3(worldTransform * pos);

    frag_color = color;
}