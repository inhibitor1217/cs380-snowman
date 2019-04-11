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

	struct WizardHatObject
	{
		Engine::RenderObject *root, *body, *bottom;
	};

	struct SantaHatObject
	{
		Engine::RenderObject *root, *body, *bottom, *end;
	};

	struct CatEarObject
	{
		Engine::RenderObject *root, *leftEar, *leftInnerEar, *rightEar, *rightInnerEar;
	};

	struct CarrotNoseObject
	{
		Engine::RenderObject *root;
	};

	struct RudolphNoseObject
	{
		Engine::RenderObject *root, *body, *end;
	};

	struct ScarfObject
	{
		Engine::RenderObject *root, *body, *branch1, *branch2, *edge1, *edge2;
	};

	struct CoatObject
	{
		Engine::RenderObject *root, *upper, *lower;
	};

	struct GloveObject
	{
		Engine::RenderObject *root, *hand, *wrist, *thumb;
	};

	struct CaneObject
	{
		Engine::RenderObject *root, *base, *center, *end1, *end2, *end3, *end4, *end5;
	};

	struct WandObject
	{
		Engine::RenderObject *root, *body;
	};

public:
	struct HatObject hat, hat_icon;
	struct WizardHatObject wizard_hat, wizard_hat_icon;
	struct SantaHatObject santa_hat, santa_hat_icon;
	struct CatEarObject cat_ear, cat_ear_icon;
	struct CarrotNoseObject carrot, carrot_icon;
	struct RudolphNoseObject rudolph, rudolph_icon;
	struct ScarfObject scarf, green_scarf_icon, red_scarf_icon;
	struct CoatObject coat, coat_icon;
	struct GloveObject glove_left, glove_right, green_glove_icon, red_glove_icon;
	struct CaneObject cane, cane_icon;
	struct WandObject wand, wand_icon;

public:
	Clothes(Geometry geometry, Engine::Material *material);

	void RenderObject(Engine::Camera *camera, DefaultMaterial *material, int index);
	void RenderUIObject(Engine::Camera *camera, DefaultMaterial *material, int index);
};