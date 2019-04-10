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

	struct ScarfObject
	{
		Engine::RenderObject *root, *body, *branch1, *branch2, *edge1, *edge2;
	};

public:
	struct HatObject hat, hat_icon;
	struct CarrotNoseObject carrot, carrot_icon;
	struct ScarfObject scarf, green_scarf_icon, red_scarf_icon;

public:
	Clothes(Geometry geometry, Engine::Material *material);

	void RenderObject(Engine::Camera *camera, DefaultMaterial *material, int index);
	void RenderUIObject(Engine::Camera *camera, DefaultMaterial *material, int index);
};