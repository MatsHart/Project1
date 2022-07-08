#pragma once
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>

using namespace std;

struct Material {
	glm::vec3 ambient_color;
	glm::vec3 diffuse_color;
	glm::vec3 specular;
	float power = 1024;
};


class Object
{
public:
	const char* filePath;
	const char* bmpPath;
	Material material = Material();
	vector<glm::vec3> normals;
	vector<glm::vec3> vertices;
	vector<glm::vec2> uvs;
	glm::mat4 model;
	glm::mat4 mv;
	GLuint texture_id;
	GLuint vao;

	Object();

	Object(const char*, const char*, glm::vec3, glm::vec3);
	Object(const char* filePath2, glm::vec3 scale, glm::vec3 translate);

	~Object() {}

	void Animate(float speed, glm::mat4);

};

