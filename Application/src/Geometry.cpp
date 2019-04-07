#include <Geometry.hpp>
#include <stdlib.h>

Geometry::Geometry()
{
}


Geometry::~Geometry()
{
}

glm::vec3 Geometry::ComputeNormal(glm::vec4 a_a, glm::vec4 a_b, glm::vec4 a_c)
{
    glm::vec3 normal = glm::normalize(glm::cross(a_b.xyz() - a_a.xyz(), a_c.xyz() - a_a.xyz()));
    return normal;
}

// TODO: Fill up Geometry::Quad (Slide No. 9)
void Geometry::Quad(Engine::Mesh* mesh, int a_a, int a_b, int a_c, int a_d)
{
	glm::vec4 vertices[8] = {
		glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f),
		glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f),
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		glm::vec4(1.0f, -1.0f, 1.0f, 1.0f),
		glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f),
		glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f),
		glm::vec4(1.0f, 1.0f, -1.0f, 1.0f),
		glm::vec4(1.0f, -1.0f, -1.0f, 1.0f)
	};
    // Compute normal for quad
    glm::vec4 n = glm::vec4(ComputeNormal(vertices[a_a], vertices[a_b], vertices[a_c]), 0.0f);
    // Triangle 1, Vertex a
    mesh->AddVertexData(vertices[a_a]);
    mesh->AddVertexData(n);
    // Triangle 1, Vertex b
    mesh->AddVertexData(vertices[a_b]);
    mesh->AddVertexData(n);
    // Triangle 1, Vertex c
    mesh->AddVertexData(vertices[a_c]);
    mesh->AddVertexData(n);
    // Triangle 2, Vertex a
    mesh->AddVertexData(vertices[a_a]);
    mesh->AddVertexData(n);
    // Triangle 2, Vertex c
    mesh->AddVertexData(vertices[a_c]);
    mesh->AddVertexData(n);
    // Triangle 2, Vertex d
    mesh->AddVertexData(vertices[a_d]);
    mesh->AddVertexData(n);
}

// TODO: Fill up Geometry::GenerateCube (Slide No. 8)
void Geometry::GenerateCube(Engine::Mesh* mesh)
{
    /*   5 -- 6
     *  /|   /|
     * 1(4)-2 7
     * |    |/
     * 0 -- 3
     */
    mesh->AddAttribute(4); // for position
    mesh->AddAttribute(4); // for normal

    // Add four quad for generating a cube
    Quad(mesh, 1, 0, 3, 2);
    Quad(mesh, 2, 3, 7, 6);
    Quad(mesh, 3, 0, 4, 7);
    Quad(mesh, 6, 5, 1, 2);
    Quad(mesh, 4, 5, 6, 7);
    Quad(mesh, 5, 4, 0, 1);

    mesh->SetNumElements(36);
    mesh->CreateMesh();
    return;
}

void Geometry::GenerateTriangleMesh(Engine::Mesh* mesh)
{
    mesh->AddAttribute(4);

    glm::vec3 position_data[] = {
        glm::vec3(-1.0f, -1.0f, 0.0f),
        glm::vec3(1.0f, -1.0f, 0.0f),
        glm::vec3(0.0f,1.0f, 0.0f)
    };

    for (int i = 0; i < 3; i++)
    {
        mesh->AddVertexData(position_data[i]);
        mesh->AddVertexData(1.0f);

    }
    mesh->SetNumElements(3);
    mesh->CreateMesh();
    return;
}

void Geometry::GenerateLine(Engine::Mesh* mesh)
{
    mesh->SetDrawMode(GL_LINES);
    mesh->AddAttribute(4);
    mesh->AddVertexData(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    mesh->AddVertexData(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    mesh->SetNumElements(2);
    mesh->CreateMesh();
    return;
}


void Geometry::GenerateStar(Engine::Mesh* mesh)
{
	mesh->AddAttribute(4);
	mesh->AddAttribute(4);

	glm::vec4 position_data[] = {
		glm::vec4(1.0f * 2.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(-0.5f * 2.0f, sqrt(0.75f) * 2.0f, 0.0f, 1.0f),
		glm::vec4(-0.5f * 2.0f, -sqrt(0.75f) * 2.0f, 0.0f, 1.0f),
		glm::vec4(-1.0f * 2.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.5f * 2.0f, -sqrt(0.75f) * 2.0f, 0.0f, 1.0f),
		glm::vec4(0.5f * 2.0f, sqrt(0.75f) * 2.0f, 0.0f, 1.0f)
	};
	glm::vec4 n = glm::vec4(ComputeNormal(position_data[0], position_data[1], position_data[2]), 0.0f);
	for (int i = 0; i < 6; i++)
	{
		mesh->AddVertexData(position_data[i]);
		mesh->AddVertexData(n);
	}

	mesh->SetNumElements(6);
	mesh->CreateMesh();

	return;
}

/* A helper function for normalizer. */
glm::vec3 normalize(glm::vec3 v)
{
	return (1.0f / sqrt(v.x * v.x + v.y * v.y + v.z * v.z)) * v;
}

void Geometry::GenerateIcosphere(Engine::Mesh *mesh, int resolution_level)
{
	mesh->AddAttribute(4); // position
	mesh->AddAttribute(4); // normal

	const float x = 0.5f * (1.0f + sqrt(5.0f));
	std::vector<glm::vec3> faces, faces_buffer;
	glm::vec3 initial_pos[12] = {
		normalize(glm::vec3(-1.0f,     x,  0.0f)),
		normalize(glm::vec3( 1.0f,     x,  0.0f)),
		normalize(glm::vec3(-1.0f,    -x,  0.0f)),
		normalize(glm::vec3( 1.0f,    -x,  0.0f)),
		normalize(glm::vec3( 0.0f, -1.0f,     x)),
		normalize(glm::vec3( 0.0f,  1.0f,     x)),
		normalize(glm::vec3( 0.0f, -1.0f,    -x)),
		normalize(glm::vec3( 0.0f,  1.0f,    -x)),
		normalize(glm::vec3(    x,  0.0f, -1.0f)),
		normalize(glm::vec3(    x,  0.0f,  1.0f)),
		normalize(glm::vec3(   -x,  0.0f, -1.0f)),
		normalize(glm::vec3(   -x,  0.0f,  1.0f))
	};
	int initial_indices[60] = {
		0, 11, 5, 0, 5, 1, 0, 1, 7, 0, 7, 10, 0, 10, 11,
		1, 5, 9, 5, 11, 4, 11, 10, 2, 10, 7, 6, 7, 1, 8,
		3, 9, 4, 3, 4, 2, 3, 2, 6, 3, 6, 8, 3, 8, 9,
		4, 9, 5, 2, 4, 11, 6, 2, 10, 8, 6, 7, 9, 8, 1
	};

	/* Add initial 20 triangles to the list. */
	for (int i = 0; i < 60; i++)
		faces.push_back(initial_pos[initial_indices[i]]);

	/* Refine triangles until the given resolution level. */
	while (resolution_level--)
	{
		faces_buffer.clear();

		for (int i = 0; i < faces.size(); i += 3)
		{
			glm::vec3 m1 = normalize(faces[i + 0] + faces[i + 1]);
			glm::vec3 m2 = normalize(faces[i + 1] + faces[i + 2]);
			glm::vec3 m3 = normalize(faces[i + 2] + faces[i + 0]);

			glm::vec3 refined_triangles[12] = {
				faces[i], m1, m3, faces[i + 1], m2, m1, faces[i + 2], m3, m2, m1, m2, m3
			};

			for (int j = 0; j < 12; j++)
				faces_buffer.push_back(refined_triangles[j]);
		}

		faces = faces_buffer;
	}

	/* Add final data into the mesh and finish creation. */
	for (auto v : faces)
	{
		mesh->AddVertexData(glm::vec4(v, 1.0f)); // position
		mesh->AddVertexData(glm::vec4(v, 1.0f)); // normal
	}

	mesh->SetNumElements(faces.size());
	mesh->CreateMesh();
}