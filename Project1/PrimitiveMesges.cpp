using namespace std

class CubeMesh{
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
};