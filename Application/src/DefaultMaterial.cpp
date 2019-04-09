#include <DefaultMaterial.hpp>

void DefaultMaterial::CreateMaterial()
{
	GLuint location;

    _program->AttachShader("Resources\\DefaultMaterial\\VertexShader.glsl", GL_VERTEX_SHADER);
    _program->AttachShader("Resources\\DefaultMaterial\\FragmentShader.glsl", GL_FRAGMENT_SHADER);
    _program->LinkShader();

    glUseProgram(_program->GetProgramId());
    location = glGetUniformLocation(_program->GetProgramId(), "color");
    glUniform4fv(location, 1, (float*)&color);
	location = glGetUniformLocation(_program->GetProgramId(), "enable_lighting");
	glUniform1f(location, enable_lighting);
}

void DefaultMaterial::UpdateColor(glm::vec4 color)
{
    glUseProgram(_program->GetProgramId());
    GLuint location = glGetUniformLocation(_program->GetProgramId(), "color");
    glUniform4fv(location, 1, (float*)&color);
}

void DefaultMaterial::UpdateEnableLighting(bool enable)
{
	enable_lighting = enable ? 1.0f : 0.0f;

	glUseProgram(_program->GetProgramId());
	GLuint location = glGetUniformLocation(_program->GetProgramId(), "enable_lighting");
	glUniform1f(location, enable_lighting);
}