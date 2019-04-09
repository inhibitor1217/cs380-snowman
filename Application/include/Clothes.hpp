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
	struct HatObject hat;
	struct CarrotNoseObject carrotNose;

public:
	Clothes(Geometry geometry, Engine::Material *material);
	~Clothes();

	void RenderHat(Engine::Camera *camera, DefaultMaterial *material);
	void RenderCarrotNose(Engine::Camera *camera, DefaultMaterial *material);
};