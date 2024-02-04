#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <cmath>


using namespace std;


//------------------------------------------------------------
// Primitive Mesh
// 
// Wrapper class for all primitve meshes so the can be drawn in the scene.
// 
// For new Primitive mesh add:
// ========================================================
// class NewMesh : public PrimitiveMesh {
// public:
//	const vector<glm::vec3>& GetVertices() const override {
//		return meshVertices;
//	}
//
//	const vector<GLuint>& GetIndices() const override {
//		return meshIndices;
//	}
// }
// =========================================================
// 
// Then set the mesh vertices and indices to the shape you want.
// 
// To implement in main.cpp -> Import the class:
//	NewMesh newMesh;
// 
// Add to createObjects() -> 
//		 objects.push_back(Object(newMesh, glm::vec3(1.0, 1.0, 1.0), glm::vec3(0, 0, 0), glm::vec3(0.0, 1.0, 0.0), 0));
//------------------------------------------------------------
class PrimitiveMesh {
public:
	virtual const vector<glm::vec3>& GetVertices() const = 0;
	virtual const vector<GLuint>& GetIndices() const = 0;
};

class CubeMesh : public PrimitiveMesh {
public:
	vector<glm::vec3> cubeVertices = {
	glm::vec3(-1.0f, -1.0f, -1.0f),
	glm::vec3(-1.0f, -1.0f,  1.0f),
	glm::vec3(-1.0f,  1.0f,  1.0f),
	glm::vec3(1.0f,  1.0f, -1.0f),
	glm::vec3(-1.0f, -1.0f, -1.0f),
	glm::vec3(-1.0f,  1.0f, -1.0f),
	glm::vec3(1.0f, -1.0f,  1.0f),
	glm::vec3(-1.0f, -1.0f, -1.0f),
	glm::vec3(1.0f, -1.0f, -1.0f),
	glm::vec3(1.0f,  1.0f, -1.0f),
	glm::vec3(1.0f, -1.0f, -1.0f),
	glm::vec3(-1.0f, -1.0f, -1.0f),
	glm::vec3(-1.0f, -1.0f, -1.0f),
	glm::vec3(-1.0f,  1.0f,  1.0f),
	glm::vec3(-1.0f,  1.0f, -1.0f),
	glm::vec3(1.0f, -1.0f,  1.0f),
	glm::vec3(-1.0f, -1.0f,  1.0f),
	glm::vec3(-1.0f, -1.0f, -1.0f),
	glm::vec3(-1.0f,  1.0f,  1.0f),
	glm::vec3(-1.0f, -1.0f,  1.0f),
	glm::vec3(1.0f, -1.0f,  1.0f),
	glm::vec3(1.0f,  1.0f,  1.0f),
	glm::vec3(1.0f, -1.0f, -1.0f),
	glm::vec3(1.0f,  1.0f, -1.0f),
	glm::vec3(1.0f, -1.0f, -1.0f),
	glm::vec3(1.0f,  1.0f,  1.0f),
	glm::vec3(1.0f, -1.0f,  1.0f),
	glm::vec3(1.0f,  1.0f,  1.0f),
	glm::vec3(1.0f,  1.0f, -1.0f),
	glm::vec3(-1.0f,  1.0f, -1.0f),
	glm::vec3(1.0f,  1.0f,  1.0f),
	glm::vec3(-1.0f,  1.0f, -1.0f),
	glm::vec3(-1.0f,  1.0f,  1.0f),
	glm::vec3(1.0f,  1.0f,  1.0f),
	glm::vec3(-1.0f,  1.0f,  1.0f),
	glm::vec3(1.0f, -1.0f,  1.0f)
	};

	vector<GLuint> cubeIndices = {
		0, 1, 2, 3, 4, 5,       // Back face
		6, 7, 8, 9, 10, 11,     // Front face
		12, 13, 14, 15, 16, 17, // Left face
		18, 19, 20, 21, 22, 23, // Right face
		24, 25, 26, 27, 28, 29, // Bottom face
		30, 31, 32, 33, 34, 35  // Top face
	};

	const vector<glm::vec3>& GetVertices() const override {
		return cubeVertices;
	}

	const vector<GLuint>& GetIndices() const override {
		return cubeIndices;
	}
};

class PyramidMesh : public PrimitiveMesh {
public:
	vector<glm::vec3> pyramidVertices = {
		// Base vertices
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, 1.0f),
		glm::vec3(-1.0f, -1.0f, 1.0f),
		// Apex vertex
		glm::vec3(0.0f, 1.0f, 0.0f)
	};

	vector<GLuint> pyramidIndices = {
		// Base indices
		0, 1, 2,
		0, 2, 3,
		// Side indices
		0, 4, 1,
		1, 4, 2,
		2, 4, 3,
		3, 4, 0
	};


	const vector<glm::vec3>& GetVertices() const override {
		return pyramidVertices;
	}

	const vector<GLuint>& GetIndices() const override {
		return pyramidIndices;
	}


};

class SphereMesh : public PrimitiveMesh {
public:
	std::vector<glm::vec3> sphereVertices;
	std::vector<GLuint> sphereIndices;

	SphereMesh(int stacks = 20, int slices = 20, float radius = 1.0f) : stacks(stacks), slices(slices), radius(radius) {
		GenerateSphereVerticesAndIndices();
	}

	const vector<glm::vec3>& GetVertices() const override {
		return sphereVertices;
	}

	const vector<GLuint>& GetIndices() const override {
		return sphereIndices;
	}

private:
	int stacks;
	int slices;
	float radius;

	void GenerateSphereVerticesAndIndices() {
		for (int i = 0; i <= stacks; i++) {
			float phi = glm::pi<float>() * static_cast<float>(i) / static_cast<float>(stacks);
			for (int j = 0; j <= slices; j++) {
				float theta = 2.0f * glm::pi<float>() * static_cast<float>(j) / static_cast<float>(slices);

				float x = radius * sin(phi) * cos(theta);
				float y = radius * cos(phi);
				float z = radius * sin(phi) * sin(theta);

				sphereVertices.push_back(glm::vec3(x, y, z));
			}
		}

		for (int i = 0; i < stacks; i++) {
			for (int j = 0; j < slices; j++) {
				int first = i * (slices + 1) + j;
				int second = first + slices + 1;

				sphereIndices.push_back(first);
				sphereIndices.push_back(second);
				sphereIndices.push_back(first + 1);

				sphereIndices.push_back(second);
				sphereIndices.push_back(second + 1);
				sphereIndices.push_back(first + 1);
			}
		}
	}
};

class CylinderMesh : public PrimitiveMesh {
public:
	std::vector<glm::vec3> cylinderVertices;
	std::vector<GLuint> cylinderIndices;

	CylinderMesh(int stacks = 20, int slices = 20, float radius = 1.0f, float height = 2.0f)
		: stacks(stacks), slices(slices), radius(radius), height(height) {
		GenerateCylinderVerticesAndIndices();
	}

	const vector<glm::vec3>& GetVertices() const override {
		return cylinderVertices;
	}

	const vector<GLuint>& GetIndices() const override {
		return cylinderIndices;
	}

private:
	int stacks;
	int slices;
	float radius;
	float height;

	void GenerateCylinderVerticesAndIndices() {
		// Calculate vertices for the sides of the cylinder
		for (int i = 0; i <= stacks; i++) {
			float phi = static_cast<float>(i) / static_cast<float>(stacks) * glm::two_pi<float>();
			float x = radius * cos(phi);
			float z = radius * sin(phi);

			for (int j = 0; j <= slices; j++) {
				float y = -height / 2.0f + static_cast<float>(j) / static_cast<float>(slices) * height;

				cylinderVertices.push_back(glm::vec3(x, y, z));
			}
		}

		// Calculate indices for the sides of the cylinder
		for (int i = 0; i < stacks; i++) {
			for (int j = 0; j < slices; j++) {
				int first = i * (slices + 1) + j;
				int second = first + slices + 1;

				cylinderIndices.push_back(first);
				cylinderIndices.push_back(second);
				cylinderIndices.push_back(first + 1);

				cylinderIndices.push_back(second);
				cylinderIndices.push_back(second + 1);
				cylinderIndices.push_back(first + 1);
			}
		}

		// Calculate vertices for the top and bottom caps of the cylinder
		for (int i = 0; i <= slices; i++) {
			float theta = static_cast<float>(i) / static_cast<float>(slices) * glm::two_pi<float>();
			float x = radius * cos(theta);
			float z = radius * sin(theta);

			// Top cap
			cylinderVertices.push_back(glm::vec3(x, height / 2.0f, z));

			// Bottom cap
			cylinderVertices.push_back(glm::vec3(x, -height / 2.0f, z));
		}

		// Calculate indices for the top and bottom caps of the cylinder
		int offset = (stacks + 1) * (slices + 1);
		for (int i = 0; i < slices; i++) {
			int topCapCenter = offset + i;
			int bottomCapCenter = offset + slices + 1 + i;

			// Top cap
			cylinderIndices.push_back(topCapCenter);
			cylinderIndices.push_back(topCapCenter + 1);
			cylinderIndices.push_back(offset + i + 1);

			// Bottom cap
			cylinderIndices.push_back(bottomCapCenter);
			cylinderIndices.push_back(bottomCapCenter + 1);
			cylinderIndices.push_back(offset + slices + 2 + i);
		}
	}
};

class ConeMesh : public PrimitiveMesh {
public:
	std::vector<glm::vec3> coneVertices;
	std::vector<GLuint> coneIndices;

	ConeMesh(int stacks = 10, float radius = 1.0f, float height = 2.0f)
		: stacks(stacks), radius(radius), height(height) {
		GeneratePartyHatVerticesAndIndices();
	}

	const vector<glm::vec3>& GetVertices() const override {
		return coneVertices;
	}

	const vector<GLuint>& GetIndices() const override {
		return coneIndices;
	}

private:
	int stacks;
	float radius;
	float height;

	void GeneratePartyHatVerticesAndIndices() {
		// Calculate vertices for the cone shape
		for (int i = 0; i <= stacks; i++) {
			float y = static_cast<float>(i) / static_cast<float>(stacks) * height;
			float currentRadius = radius - (i / static_cast<float>(stacks)) * radius;

			for (int j = 0; j <= stacks; j++) {
				float theta = 2.0f * glm::pi<float>() * static_cast<float>(j) / static_cast<float>(stacks);
				float x = currentRadius * cos(theta);
				float z = currentRadius * sin(theta);

				coneVertices.push_back(glm::vec3(x, y, z));
			}
		}

		// Calculate indices to form triangles
		for (int i = 0; i < stacks; i++) {
			for (int j = 0; j < stacks; j++) {
				int currentRow = i * (stacks + 1);
				int nextRow = (i + 1) * (stacks + 1);

				coneIndices.push_back(currentRow + j);
				coneIndices.push_back(nextRow + j);
				coneIndices.push_back(currentRow + j + 1);

				coneIndices.push_back(currentRow + j + 1);
				coneIndices.push_back(nextRow + j);
				coneIndices.push_back(nextRow + j + 1);
			}
		}
	}
};

class DonutMesh : public PrimitiveMesh {
public:
	std::vector<glm::vec3> donutVertices;
	std::vector<GLuint> donutIndices;

	DonutMesh(int stacks = 20, int slices = 40, float majorRadius = 1.0f, float minorRadius = 0.3f)
		: stacks(stacks), slices(slices), majorRadius(majorRadius), minorRadius(minorRadius) {
		GenerateDonutVerticesAndIndices();
	}

	const std::vector<glm::vec3>& GetVertices() const {
		return donutVertices;
	}

	const std::vector<GLuint>& GetIndices() const {
		return donutIndices;
	}

private:
	int stacks;
	int slices;
	float majorRadius;
	float minorRadius;

	void GenerateDonutVerticesAndIndices() {
		for (int i = 0; i <= stacks; i++) {
			float phi = glm::two_pi<float>() * static_cast<float>(i) / static_cast<float>(stacks);
			float cosPhi = cos(phi);
			float sinPhi = sin(phi);

			for (int j = 0; j <= slices; j++) {
				float theta = glm::two_pi<float>() * static_cast<float>(j) / static_cast<float>(slices);
				float cosTheta = cos(theta);
				float sinTheta = sin(theta);

				float x = (majorRadius + minorRadius * cosTheta) * cosPhi;
				float y = minorRadius * sinTheta;
				float z = (majorRadius + minorRadius * cosTheta) * sinPhi;

				donutVertices.push_back(glm::vec3(x, y, z));
			}
		}

		for (int i = 0; i < stacks; i++) {
			for (int j = 0; j < slices; j++) {
				int currentRow = i * (slices + 1);
				int nextRow = (i + 1) * (slices + 1);

				donutIndices.push_back(currentRow + j);
				donutIndices.push_back(nextRow + j);
				donutIndices.push_back(currentRow + j + 1);

				donutIndices.push_back(currentRow + j + 1);
				donutIndices.push_back(nextRow + j);
				donutIndices.push_back(nextRow + j + 1);
			}
		}
	}
};
