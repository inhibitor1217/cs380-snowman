#include <Geometry.hpp>
#include <stdlib.h>

constexpr float PI = 3.1415926f;
extern float randf(float, float);

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

void Geometry::GenerateTriangle(Engine::Mesh* mesh)
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

void Geometry::GenerateIcosphere(Engine::Mesh *mesh, int resolution_level)
{
	mesh->AddAttribute(4); // position
	mesh->AddAttribute(4); // normal

	const float x = 0.5f * (1.0f + sqrt(5.0f));
	std::vector<glm::vec3> faces, faces_buffer;
	glm::vec3 initial_pos[12] = {
		glm::normalize(glm::vec3(-1.0f,     x,  0.0f)),
		glm::normalize(glm::vec3( 1.0f,     x,  0.0f)),
		glm::normalize(glm::vec3(-1.0f,    -x,  0.0f)),
		glm::normalize(glm::vec3( 1.0f,    -x,  0.0f)),
		glm::normalize(glm::vec3( 0.0f, -1.0f,     x)),
		glm::normalize(glm::vec3( 0.0f,  1.0f,     x)),
		glm::normalize(glm::vec3( 0.0f, -1.0f,    -x)),
		glm::normalize(glm::vec3( 0.0f,  1.0f,    -x)),
		glm::normalize(glm::vec3(    x,  0.0f, -1.0f)),
		glm::normalize(glm::vec3(    x,  0.0f,  1.0f)),
		glm::normalize(glm::vec3(   -x,  0.0f, -1.0f)),
		glm::normalize(glm::vec3(   -x,  0.0f,  1.0f))
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
			glm::vec3 m1 = glm::normalize(faces[i + 0] + faces[i + 1]);
			glm::vec3 m2 = glm::normalize(faces[i + 1] + faces[i + 2]);
			glm::vec3 m3 = glm::normalize(faces[i + 2] + faces[i + 0]);

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
		mesh->AddVertexData(glm::vec4(v, 1.0f) 
			+ glm::vec4(randf(-0.03f, 0.03f), randf(-0.03f, 0.03f), randf(-0.03f, 0.03f), 0.0f)); // normal
	}

	mesh->SetNumElements(faces.size());
	mesh->CreateMesh();
}

void Geometry::GenerateCylinder(Engine::Mesh *mesh, int polygon)
{
	if (polygon < 3)
	{
		std::cout << "GenerateCylinder: assert fails at polygon >= 3" << std::endl;
		throw std::exception();
	}

	const float angle = 2 * PI / static_cast<float>(polygon);

	mesh->AddAttribute(4); // position
	mesh->AddAttribute(4); // normal

	/* Add top faces. */
	for (int i = 0; i < polygon; i++)
	{
		mesh->AddVertexData(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
		mesh->AddVertexData(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

		mesh->AddVertexData(glm::vec4(cos(angle * i), sin(angle * i), 1.0f, 1.0f));
		mesh->AddVertexData(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

		mesh->AddVertexData(glm::vec4(cos(angle * (i + 1)), sin(angle * (i + 1)), 1.0f, 1.0f));
		mesh->AddVertexData(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	}

	/* Add bottom faces. */
	for (int i = 0; i < polygon; i++)
	{
		mesh->AddVertexData(glm::vec4(0.0f, 0.0f, -1.0f, 1.0f));
		mesh->AddVertexData(glm::vec4(0.0f, 0.0f, -1.0f, 1.0f));

		mesh->AddVertexData(glm::vec4(cos(angle * (i + 1)), sin(angle * (i + 1)), -1.0f, 1.0f));
		mesh->AddVertexData(glm::vec4(0.0f, 0.0f, -1.0f, 1.0f));

		mesh->AddVertexData(glm::vec4(cos(angle * i), sin(angle * i), -1.0f, 1.0f));
		mesh->AddVertexData(glm::vec4(0.0f, 0.0f, -1.0f, 1.0f));
	}

	/* Add side faces. */
	for (int i = 0; i < polygon; i++)
	{
		mesh->AddVertexData(glm::vec4(cos(angle * i), sin(angle * i), 1.0f, 1.0f));
		mesh->AddVertexData(glm::vec4(cos(angle * i), sin(angle * i), 0.0f, 1.0f));

		mesh->AddVertexData(glm::vec4(cos(angle * i), sin(angle * i), -1.0f, 1.0f));
		mesh->AddVertexData(glm::vec4(cos(angle * i), sin(angle * i), 0.0f, 1.0f));

		mesh->AddVertexData(glm::vec4(cos(angle * (i + 1)), sin(angle * (i + 1)), -1.0f, 1.0f));
		mesh->AddVertexData(glm::vec4(cos(angle * (i + 1)), sin(angle * (i + 1)), 0.0f, 1.0f));

		mesh->AddVertexData(glm::vec4(cos(angle * i), sin(angle * i), 1.0f, 1.0f));
		mesh->AddVertexData(glm::vec4(cos(angle * i), sin(angle * i), 0.0f, 1.0f));

		mesh->AddVertexData(glm::vec4(cos(angle * (i + 1)), sin(angle * (i + 1)), -1.0f, 1.0f));
		mesh->AddVertexData(glm::vec4(cos(angle * (i + 1)), sin(angle * (i + 1)), 0.0f, 1.0f));

		mesh->AddVertexData(glm::vec4(cos(angle * (i + 1)), sin(angle * (i + 1)), 1.0f, 1.0f));
		mesh->AddVertexData(glm::vec4(cos(angle * (i + 1)), sin(angle * (i + 1)), 0.0f, 1.0f));
	}

	mesh->SetNumElements(12 * polygon);
	mesh->CreateMesh();
}

void Geometry::GenerateCylinder(Engine::Mesh *mesh, int polygon, float top_radius, float bottom_radius)
{
	if (polygon < 3)
	{
		std::cout << "GenerateCylinder: assert fails at polygon >= 3" << std::endl;
		throw std::exception();
	}

	const float angle = 2 * PI / static_cast<float>(polygon);

	mesh->AddAttribute(4); // position
	mesh->AddAttribute(4); // normal

	/* Add top faces. */
	for (int i = 0; i < polygon; i++)
	{
		mesh->AddVertexData(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
		mesh->AddVertexData(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

		mesh->AddVertexData(glm::vec4(top_radius * cos(angle * i), top_radius * sin(angle * i), 1.0f, 1.0f));
		mesh->AddVertexData(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

		mesh->AddVertexData(glm::vec4(top_radius * cos(angle * (i + 1)), top_radius * sin(angle * (i + 1)), 1.0f, 1.0f));
		mesh->AddVertexData(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	}

	/* Add bottom faces. */
	for (int i = 0; i < polygon; i++)
	{
		mesh->AddVertexData(glm::vec4(0.0f, 0.0f, -1.0f, 1.0f));
		mesh->AddVertexData(glm::vec4(0.0f, 0.0f, -1.0f, 1.0f));

		mesh->AddVertexData(glm::vec4(bottom_radius * cos(angle * (i + 1.5f)), bottom_radius * sin(angle * (i + 1.5f)), -1.0f, 1.0f));
		mesh->AddVertexData(glm::vec4(0.0f, 0.0f, -1.0f, 1.0f));

		mesh->AddVertexData(glm::vec4(bottom_radius * cos(angle * (i + 0.5f)), bottom_radius * sin(angle * (i + 0.5f)), -1.0f, 1.0f));
		mesh->AddVertexData(glm::vec4(0.0f, 0.0f, -1.0f, 1.0f));
	}

	/* Add side faces. */
	for (int i = 0; i < polygon; i++)
	{
		float normal_z = 0.5f * (bottom_radius - top_radius);

		mesh->AddVertexData(glm::vec4(top_radius * cos(angle * i), top_radius * sin(angle * i), 1.0f, 1.0f));
		mesh->AddVertexData(glm::vec4(cos(angle * i), sin(angle * i), normal_z, 1.0f));

		mesh->AddVertexData(glm::vec4(bottom_radius * cos(angle * (i + 0.5f)), bottom_radius * sin(angle * (i + 0.5f)), -1.0f, 1.0f));
		mesh->AddVertexData(glm::vec4(cos(angle * (i + 0.5f)), sin(angle * (i + 0.5f)), normal_z, 1.0f));

		mesh->AddVertexData(glm::vec4(top_radius * cos(angle * (i + 1)), top_radius * sin(angle * (i + 1)), 1.0f, 1.0f));
		mesh->AddVertexData(glm::vec4(cos(angle * (i + 1)), sin(angle * (i + 1)), normal_z, 1.0f));

		mesh->AddVertexData(glm::vec4(bottom_radius * cos(angle * (i + 0.5f)), bottom_radius * sin(angle * (i + 0.5f)), -1.0f, 1.0f));
		mesh->AddVertexData(glm::vec4(cos(angle * (i + 0.5f)), sin(angle * (i + 0.5f)), normal_z, 1.0f));

		mesh->AddVertexData(glm::vec4(bottom_radius * cos(angle * (i + 1.5f)), bottom_radius * sin(angle * (i + 1.5f)), -1.0f, 1.0f));
		mesh->AddVertexData(glm::vec4(cos(angle * (i + 1.5f)), sin(angle * (i + 1.5f)), normal_z, 1.0f));

		mesh->AddVertexData(glm::vec4(top_radius * cos(angle * (i + 1)), top_radius * sin(angle * (i + 1)), 1.0f, 1.0f));
		mesh->AddVertexData(glm::vec4(cos(angle * (i + 1)), sin(angle * (i + 1)), normal_z, 1.0f));
	}

	mesh->SetNumElements(12 * polygon);
	mesh->CreateMesh();
}

void Geometry::GenerateCone(Engine::Mesh *mesh, int polygon)
{
	if (polygon < 3)
	{
		std::cout << "GenerateCone: assert fails at polygon >= 3" << std::endl;
		throw std::exception();
	}

	const float angle = 2 * PI / static_cast<float>(polygon);

	mesh->AddAttribute(4); // position
	mesh->AddAttribute(4); // normal

	/* Add bottom faces. */
	for (int i = 0; i < polygon; i++)
	{
		mesh->AddVertexData(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		mesh->AddVertexData(glm::vec4(0.0f, 0.0f, -1.0f, 1.0f));

		mesh->AddVertexData(glm::vec4(cos(angle * (i + 1)), sin(angle * (i + 1)), 0.0f, 1.0f));
		mesh->AddVertexData(glm::vec4(0.0f, 0.0f, -1.0f, 1.0f));

		mesh->AddVertexData(glm::vec4(cos(angle * i), sin(angle * i), 0.0f, 1.0f));
		mesh->AddVertexData(glm::vec4(0.0f, 0.0f, -1.0f, 1.0f));
	}

	/* Add side faces. */
	for (int i = 0; i < polygon; i++)
	{
		mesh->AddVertexData(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
		mesh->AddVertexData(glm::vec4(cos(angle * (i + 0.5f)), sin(angle * (i + 0.5f)), 1.0f, 1.0f));

		mesh->AddVertexData(glm::vec4(cos(angle * i), sin(angle * i), 0.0f, 1.0f));
		mesh->AddVertexData(glm::vec4(cos(angle * i), sin(angle * i), 1.0f, 1.0f));

		mesh->AddVertexData(glm::vec4(cos(angle * (i + 1)), sin(angle * (i + 1)), 0.0f, 1.0f));
		mesh->AddVertexData(glm::vec4(cos(angle * (i + 1)), sin(angle * (i + 1)), 1.0f, 1.0f));
	}

	mesh->SetNumElements(6 * polygon);
	mesh->CreateMesh();
}

void Geometry::GenerateSquare(Engine::Mesh *mesh)
{
	mesh->AddAttribute(4); // position
	mesh->AddAttribute(4); // normal

	glm::vec3 positions[] = {
		glm::vec3(-0.5f, 0.5f, 0.0f),
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3(0.5f, 0.5f, 0.0f),
		glm::vec3(0.5f, -0.5f, 0.0f)
	};

	int indices[] = { 0, 1, 3, 0, 3, 2 };

	for (int i = 0; i < 6; i++)
	{
		mesh->AddVertexData(glm::vec4(positions[indices[i]], 1.0f));
		mesh->AddVertexData(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	}

	mesh->SetNumElements(6);
	mesh->CreateMesh();
}

void Geometry::GenerateTerrainMesh(Engine::Mesh *mesh)
{
	mesh->AddAttribute(4); // position
	mesh->AddAttribute(4); // color
	mesh->AddAttribute(4); // normal

	int terrain_resolution = 5;

	const float angle = PI / 3.0f;
	std::vector<glm::vec3> faces, faces_buffer;
	glm::vec3 initial_pos[] = {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(cos(angle * 0), sin(angle * 0), 0.0f),
		glm::vec3(cos(angle * 1), sin(angle * 1), 0.0f),
		glm::vec3(cos(angle * 2), sin(angle * 2), 0.0f),
		glm::vec3(cos(angle * 3), sin(angle * 3), 0.0f),
		glm::vec3(cos(angle * 4), sin(angle * 4), 0.0f),
		glm::vec3(cos(angle * 5), sin(angle * 5), 0.0f)
	};
	int initial_indices[] = {
		0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 5, 0, 5, 6, 0, 6, 1
	};

	for (int i = 0; i < 18; i++)
		faces.push_back(initial_pos[initial_indices[i]]);

	while (terrain_resolution--)
	{
		faces_buffer.clear();

		for (int i = 0; i < faces.size(); i += 3)
		{
			glm::vec3 m1 = 0.5f * (faces[i + 0] + faces[i + 1]);
			glm::vec3 m2 = 0.5f * (faces[i + 1] + faces[i + 2]);
			glm::vec3 m3 = 0.5f * (faces[i + 2] + faces[i + 0]);

			glm::vec3 refined_triangles[12] = {
				faces[i], m1, m3, faces[i + 1], m2, m1, faces[i + 2], m3, m2, m1, m2, m3
			};

			for (int j = 0; j < 12; j++)
				faces_buffer.push_back(refined_triangles[j]);
		}

		faces = faces_buffer;
	}

	/* Add final data into the mesh and finish creation. */
	for (int i = 0; i < faces.size(); i += 3)
	{
		glm::vec3 normal = glm::vec3(randf(-0.1f, 0.1f), randf(-0.1f, 0.1f), 1.0f);

		mesh->AddVertexData(glm::vec4(faces[i], 1.0f)); // position
		mesh->AddVertexData(glm::vec4(0.2f)); // color
		mesh->AddVertexData(glm::vec4(normal, 1.0f)); // normal

		mesh->AddVertexData(glm::vec4(faces[i + 1], 1.0f)); // position
		mesh->AddVertexData(glm::vec4(0.2f)); // color
		mesh->AddVertexData(glm::vec4(normal, 1.0f)); // normal

		mesh->AddVertexData(glm::vec4(faces[i + 2], 1.0f)); // position
		mesh->AddVertexData(glm::vec4(0.2f)); // color
		mesh->AddVertexData(glm::vec4(normal, 1.0f)); // normal
	}

	mesh->SetNumElements(faces.size());
	mesh->CreateMesh();
}