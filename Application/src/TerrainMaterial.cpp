#include "TerrainMaterial.hpp"

void TerrainMaterial::CreateMaterial()
{
	_program->AttachShader("Resources\\TerrainMaterial\\TerrainVertexShader.glsl", GL_VERTEX_SHADER);
	_program->AttachShader("Resources\\TerrainMaterial\\TerrainFragmentShader.glsl", GL_FRAGMENT_SHADER);
	_program->LinkShader();
}