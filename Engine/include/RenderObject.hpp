#pragma once

#include <iostream>
#include <exception>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Camera.hpp>
#include <Mesh.hpp>
#include <Material.hpp>
#include <vector>

namespace Engine
{
	class Camera; // forward definition

    class RenderObject
    {
    private:
        glm::vec3 _position;
        glm::mat4 _orientation;
        glm::vec3 _scale;

		float _rotation_speed;


    protected:
        Mesh* _mesh;
        Material* _material;
		int _index;

		//TO DO implement hierarchical structure
		RenderObject *parent = NULL;

		

    public:
        RenderObject();
        RenderObject(Mesh* mesh, Material* material);


		virtual void ChangeMaterial(Material* mat);
        virtual void Render(Camera* cam);
        virtual void SetMesh(Mesh* mesh) { _mesh = mesh; }
        virtual void SetMaterial(Material* material) { _material = material; }
        virtual glm::vec3 GetPosition() { return _position; }
        virtual void SetPosition(glm::vec3 position) { _position = position; }
        virtual glm::mat4 GetOrientation() { return _orientation; }
        virtual void SetOrientation(glm::mat4 orientation) { _orientation = orientation; }
        virtual glm::vec3 GetScale() { return _scale; }
        virtual void SetScale(glm::vec3 scale) { _scale = scale; }
        virtual glm::mat4 GetWorldTransform();

		virtual int GetIndex() { return _index; }
		virtual void SetIndex(int index) { _index = index; }

		virtual void AddParent(RenderObject *parent_object) { parent = parent_object; };



    };
}