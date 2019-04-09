#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <PickableObject.hpp>
#include "Geometry.hpp"
#include "DefaultMaterial.hpp"

class Snowman
{
private:
	Engine::RenderObject *b_base;
	Engine::RenderObject *b_torso;
	Engine::RenderObject *b_head;
	Engine::RenderObject *b_nose;
	Engine::RenderObject *b_headAccessory;

	Engine::RenderObject *base;
	Engine::RenderObject *torso;
	Engine::RenderObject *head;
	Engine::RenderObject *leftEye;
	Engine::RenderObject *rightEye;
	Engine::RenderObject *button1, *button2, *button3, *button4, *button5;

	Engine::RenderObject *nose;
	Engine::RenderObject *headAccessory = nullptr;

public:
    Snowman(Geometry geometry, Engine::Material *material);

	Engine::RenderObject *GetRootObject() { return b_torso; }
	
	void SetHeadAccessory(Engine::RenderObject *obj);
	void SetNose(Engine::RenderObject *obj);

	void Render(Engine::Camera *cam, DefaultMaterial *material);
};