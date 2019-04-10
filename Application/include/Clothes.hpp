#pragma once

#include "RenderObject.hpp"
#include "Mesh.hpp"
#include "Material.hpp"
#include "Geometry.hpp"
#include "DefaultMaterial.hpp"

class Clothes
{
private:
	struct HatObject
	{
		Engine::RenderObject *root, *body, *ribbon, *bottom;
	};

	struct CarrotNoseObject
	{
		Engine::RenderObject *root;
	};

public:
	struct HatObject hat, ui_hat;
	struct CarrotNoseObject carrotNose;

public:
	Clothes(Geometry geometry, Engine::Material *material);

	void RenderObject(Engine::Camera *camera, DefaultMaterial *material, int index);
	void RenderUIObject(Engine::Camera *camera, DefaultMaterial *material, int index);
};