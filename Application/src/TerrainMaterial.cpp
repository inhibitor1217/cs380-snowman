#include "TerrainMaterial.hpp"

void TerrainMaterial::CreateMaterial()
{
	_program->AttachShader("Resources\\TerrainMaterial\\TerrainVertexShader.glsl", GL_VERTEX_SHADER);
	_program->AttachShader("Resources\\TerrainMaterial\\TerrainFragmentShader.glsl", GL_FRAGMENT_SHADER);
	_program->LinkShader();

	glm::vec4 color = glm::vec4(1.0f);

	glUseProgram(_program->GetProgramId());
	GLuint location = glGetUniformLocation(_program->GetProgramId(), "global_color");
	glUniform4fv(location, 1, (float*)&color);
}

void TerrainMaterial::UpdateGlobalColor(glm::vec4 color)
{
	glUseProgram(_program->GetProgramId());
	GLuint location = glGetUniformLocation(_program->GetProgramId(), "global_color");
	glUniform4fv(location, 1, (float*)&color);
}