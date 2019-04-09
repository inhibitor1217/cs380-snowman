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

public:
	struct HatObject hat;

public:
	Clothes(Geometry geometry, Engine::Material *material);
	~Clothes();

	void RenderHat(Engine::Camera *camera, DefaultMaterial *material);
};