#include <Snowman.hpp>

Snowman::Snowman(Engine::Mesh *sphereMesh, Engine::Material *material)
{
	b_base = new Engine::RenderObject(nullptr, nullptr);
	b_base->SetPosition(glm::vec3(0.0f, 0.0f, 0.5f));
	b_torso = new Engine::RenderObject(nullptr, nullptr);
	b_torso->AddParent(b_base);
	b_torso->SetPosition(glm::vec3(0.0f, 0.0f, 1.4f));
	b_head = new Engine::RenderObject(nullptr, nullptr);
	b_head->AddParent(b_torso);
	b_head->SetPosition(glm::vec3(0.0f, 0.0f, 1.2f));

	base = new Engine::RenderObject(sphereMesh, material);
	base->AddParent(b_base);
	torso = new Engine::RenderObject(sphereMesh, material);
	torso->AddParent(b_torso);
	torso->SetScale(glm::vec3(0.8f, 0.8f, 0.8f));
	head = new Engine::RenderObject(sphereMesh, material);
	head->AddParent(b_head);
	head->SetScale(glm::vec3(0.6f, 0.6f, 0.6f));
}

Snowman::~Snowman()
{
	delete b_base;
	delete b_torso;
	delete b_head;

	delete base;
	delete torso;
	delete head;
}

void Snowman::Render(Engine::Camera *cam)
{
	base->Render(cam);
	torso->Render(cam);
	head->Render(cam);
}