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
	Engine::RenderObject *b_torsoJoint;
	Engine::RenderObject *b_torso;
	Engine::RenderObject *b_headJoint;
	Engine::RenderObject *b_head;
	Engine::RenderObject *b_nose;
	Engine::RenderObject *b_headAccessory;
	Engine::RenderObject *b_torsoAccessory;
	Engine::RenderObject *b_leftShoulder;
	Engine::RenderObject *b_leftArm;
	Engine::RenderObject *b_leftHand;
	Engine::RenderObject *b_rightShoulder;
	Engine::RenderObject *b_rightArm;
	Engine::RenderObject *b_rightHand;

	Engine::RenderObject *base;
	Engine::RenderObject *torso;
	Engine::RenderObject *head;
	Engine::RenderObject *leftEye;
	Engine::RenderObject *rightEye;
	Engine::RenderObject *button1, *button2, *button3, *button4, *button5;
	Engine::RenderObject *leftArm;
	Engine::RenderObject *leftArmBranch1;
	Engine::RenderObject *leftArmBranch2;
	Engine::RenderObject *rightArm;
	Engine::RenderObject *rightArmBranch1;

	friend class Animation;

public:
    Snowman(Geometry geometry, Engine::Material *material);

	Engine::RenderObject *GetRootObject() { return b_torso; }
	
	void SetHeadAccessory(Engine::RenderObject *obj);
	void SetNose(Engine::RenderObject *obj);
	void SetTorsoAccessory(Engine::RenderObject *obj);
	void SetHandAccessory(Engine::RenderObject *obj_left, Engine::RenderObject *obj_right);

	void Render(Engine::Camera *cam, DefaultMaterial *material);
};