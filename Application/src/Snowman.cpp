#include <Snowman.hpp>

constexpr float PI = 3.1415926f;

Snowman::Snowman(Geometry geometry, Engine::Material *material)
{
	Engine::Mesh *sphereMesh = new Engine::Mesh();
	geometry.GenerateIcosphere(sphereMesh, 3);

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