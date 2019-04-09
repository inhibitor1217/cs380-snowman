#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <PickableObject.hpp>

class Snowman
{
private:
	Engine::RenderObject *b_base;
	Engine::RenderObject *b_torso;
	Engine::RenderObject *b_head;

	Engine::RenderObject *base;
	Engine::RenderObject *torso;
	Engine::RenderObject *head;

public:
    Snowman(Engine::Mesh *sphereMesh, Engine::Material *material);
    ~Snowman();

	Engine::RenderObject *GetRootObject() { return b_torso; }

	void Render(Engine::Camera *cam);
};