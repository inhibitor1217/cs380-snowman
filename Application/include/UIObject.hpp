#pragma once

#include <Mesh.hpp>
#include <Material.hpp>
#include <RenderObject.hpp>

class UIObject: virtual public Engine::RenderObject
{
protected:
	glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f);

public:
	UIObject(Engine::Mesh *mesh, Engine::Material *material);
	~UIObject();

	void SetColor(glm::vec3 color) { _color = color; }
	glm::vec3 GetColor() { return _color; }

	virtual glm::vec3 GetRenderColor() { return _color; }
};

