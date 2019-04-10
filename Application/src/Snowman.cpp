#include <Snowman.hpp>

constexpr float PI = 3.1415926f;

Snowman::Snowman(Geometry geometry, Engine::Material *material)
{
	Engine::Mesh *sphereMesh = new Engine::Mesh();
	geometry.GenerateIcosphere(sphereMesh, 3);
	Engine::Mesh *cylinderMesh = new Engine::Mesh();
	geometry.GenerateCylinder(cylinderMesh, 12, 0.2f, 1.0f);

	b_base = new Engine::RenderObject(nullptr, nullptr);
	b_base->SetPosition(glm::vec3(0.0f, 0.0f, 0.5f));
	b_torso = new Engine::RenderObject(nullptr, nullptr);
	b_torso->AddParent(b_base);
	b_torso->SetPosition(glm::vec3(0.0f, 0.0f, 1.4f));
	b_head = new Engine::RenderObject(nullptr, nullptr);
	b_head->AddParent(b_torso);
	b_nose = new Engine::RenderObject(nullptr, nullptr);
	b_nose->AddParent(b_head);
	b_nose->SetPosition(glm::vec3(0.0f, -0.6f, 0.0f));
	b_nose->SetOrientation(glm::rotate(
		glm::mat4(1.0f), 0.5f * PI, glm::vec3(1.0f, 0.0f, 0.0f)
	));
	b_head->SetPosition(glm::vec3(0.0f, 0.0f, 1.2f));
	b_headAccessory = new Engine::RenderObject(nullptr, nullptr);
	b_headAccessory->AddParent(b_head);
	b_headAccessory->SetPosition(glm::vec3(-0.1f, -0.1f, 1.0f));
	b_headAccessory->SetOrientation(glm::rotate(
		glm::mat4(1.0f), 0.1f, glm::vec3(1.0f, -1.0f, 0.0f)
	));
	b_torsoAccessory = new Engine::RenderObject(nullptr, nullptr);
	b_torsoAccessory->AddParent(b_torso);
	b_torsoAccessory->SetPosition(glm::vec3(0.0f, 0.0f, 0.5f));
	b_leftShoulder = new Engine::RenderObject(nullptr, nullptr);
	b_leftShoulder->AddParent(b_torso);
	b_leftShoulder->SetOrientation(glm::rotate(
		glm::mat4(1.0f), 1.2f, glm::vec3(0.0f, 1.0f, -0.1f)
	));
	b_leftArm = new Engine::RenderObject(nullptr, nullptr);
	b_leftArm->AddParent(b_leftShoulder);
	b_leftArm->SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));
	b_leftHand = new Engine::RenderObject(nullptr, nullptr);
	b_leftHand->AddParent(b_leftArm);
	b_leftHand->SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));
	b_rightShoulder = new Engine::RenderObject(nullptr, nullptr);
	b_rightShoulder->AddParent(b_torso);
	b_rightShoulder->SetOrientation(glm::rotate(
		glm::mat4(1.0f), -1.4f, glm::vec3(0.0f, 1.0f, -0.2f)
	));
	b_rightArm = new Engine::RenderObject(nullptr, nullptr);
	b_rightArm->AddParent(b_rightShoulder);
	b_rightArm->SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));
	b_rightHand = new Engine::RenderObject(nullptr, nullptr);
	b_rightHand->AddParent(b_rightArm);
	b_rightHand->SetPosition(glm::vec3(0.0f, 0.0f, 1.0f));


	base = new Engine::RenderObject(sphereMesh, material);
	base->AddParent(b_base);
	torso = new Engine::RenderObject(sphereMesh, material);
	torso->AddParent(b_torso);
	torso->SetScale(glm::vec3(0.8f, 0.8f, 0.8f));
	head = new Engine::RenderObject(sphereMesh, material);
	head->AddParent(b_head);
	head->SetScale(glm::vec3(0.6f, 0.6f, 0.6f));
	leftEye = new Engine::RenderObject(sphereMesh, material);
	leftEye->AddParent(b_head);
	leftEye->SetScale(glm::vec3(0.05f, 0.05f, 0.08f));
	leftEye->SetPosition(glm::vec3(0.2f, -0.55f, 0.1f));
	rightEye = new Engine::RenderObject(sphereMesh, material);
	rightEye->AddParent(b_head);
	rightEye->SetScale(glm::vec3(0.05f, 0.05f, 0.08f));
	rightEye->SetPosition(glm::vec3(-0.2f, -0.55f, 0.1f));
	button1 = new Engine::RenderObject(sphereMesh, material);
	button1->AddParent(b_torso);
	button1->SetScale(glm::vec3(0.06f, 0.06f, 0.06f));
	button1->SetPosition(glm::vec3(0.0f, -0.67f, 0.4f));
	button2 = new Engine::RenderObject(sphereMesh, material);
	button2->AddParent(b_torso);
	button2->SetScale(glm::vec3(0.09f, 0.09f, 0.09f));
	button2->SetPosition(glm::vec3(0.0f, -0.77f, 0.0f));
	button3 = new Engine::RenderObject(sphereMesh, material);
	button3->AddParent(b_torso);
	button3->SetScale(glm::vec3(0.05f, 0.05f, 0.05f));
	button3->SetPosition(glm::vec3(0.0f, -0.67f, -0.4f));
	button4 = new Engine::RenderObject(sphereMesh, material);
	button4->AddParent(b_base);
	button4->SetScale(glm::vec3(0.05f, 0.05f, 0.05f));
	button4->SetPosition(glm::vec3(0.0f, -0.87f, 0.5f));
	button5 = new Engine::RenderObject(sphereMesh, material);
	button5->AddParent(b_base);
	button5->SetScale(glm::vec3(0.07f, 0.07f, 0.07f));
	button5->SetPosition(glm::vec3(0.0f, -1.0f, 0.0f));
	leftArm = new Engine::RenderObject(cylinderMesh, material);
	leftArm->AddParent(b_leftArm);
	leftArm->SetScale(glm::vec3(0.06f, 0.06f, 1.0f));
	leftArmBranch1 = new Engine::RenderObject(cylinderMesh, material);
	leftArmBranch1->AddParent(b_leftArm);
	leftArmBranch1->SetPosition(glm::vec3(0.0f, 0.0f, 0.5f)
		+ glm::vec3(glm::rotate(
			glm::mat4(1.0f), 1.2f, glm::vec3(1.0f, 1.0f, 1.0f)
		) * glm::vec4(0.0f, 0.0f, 0.24f, 1.0f)));
	leftArmBranch1->SetOrientation(glm::rotate(
		glm::mat4(1.0f), 1.2f, glm::vec3(1.0f, 1.0f, 1.0f)
	));
	leftArmBranch1->SetScale(glm::vec3(0.02f, 0.02f, 0.24f));
	leftArmBranch2 = new Engine::RenderObject(cylinderMesh, material);
	leftArmBranch2->AddParent(b_leftArm);
	leftArmBranch2->SetPosition(glm::vec3(0.0f, 0.0f, 0.7f)
		+ glm::vec3(glm::rotate(
			glm::mat4(1.0f), 0.7f, glm::vec3(-2.0f, -1.0f, -0.5f)
		) * glm::vec4(0.0f, 0.0f, 0.12f, 1.0f)));
	leftArmBranch2->SetOrientation(glm::rotate(
		glm::mat4(1.0f), 0.7f, glm::vec3(-2.0f, -1.0f, -0.5f)
	));
	leftArmBranch2->SetScale(glm::vec3(0.01f, 0.01f, 0.12f));
	rightArm = new Engine::RenderObject(cylinderMesh, material);
	rightArm->AddParent(b_rightArm);
	rightArm->SetScale(glm::vec3(0.06f, 0.06f, 1.0f));
	rightArmBranch1 = new Engine::RenderObject(cylinderMesh, material);
	rightArmBranch1->AddParent(b_rightArm);
	rightArmBranch1->SetPosition(glm::vec3(0.0f, 0.0f, 0.7f)
			+ glm::vec3(glm::rotate(
				glm::mat4(1.0f), 0.7f, glm::vec3(-1.0f, 1.0f, -0.5f)
			) * glm::vec4(0.0f, 0.0f, 0.12f, 1.0f)));
	rightArmBranch1->SetOrientation(glm::rotate(
		glm::mat4(1.0f), 0.7f, glm::vec3(-1.0f, 1.0f, -0.5f)
	));
	rightArmBranch1->SetScale(glm::vec3(0.01f, 0.01f, 0.12f));
}

void Snowman::Render(Engine::Camera *cam, DefaultMaterial *material)
{
	material->UpdateColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	base->Render(cam);
	torso->Render(cam);
	head->Render(cam);
	material->UpdateColor(glm::vec4(0.1f, 0.1f, 0.1f, 0.1f));
	leftEye->Render(cam);
	rightEye->Render(cam);
	button1->Render(cam);
	button2->Render(cam);
	button3->Render(cam);
	button4->Render(cam);
	button5->Render(cam);
	material->UpdateColor(glm::vec4(0x60 / 255.0f, 0x41 / 255.0f, 0x2B / 255.0f, 0.1f));
	leftArm->Render(cam);
	leftArmBranch1->Render(cam);
	leftArmBranch2->Render(cam);
	rightArm->Render(cam);
	rightArmBranch1->Render(cam);
}

void Snowman::SetHeadAccessory(Engine::RenderObject *obj)
{
	obj->AddParent(b_headAccessory);
	headAccessory = obj;
}

void Snowman::SetNose(Engine::RenderObject *obj)
{
	obj->AddParent(b_nose);
	nose = obj;
}

void Snowman::SetTorsoAccessory(Engine::RenderObject *obj)
{
	obj->AddParent(b_torsoAccessory);
	torsoAccessory = obj;
}