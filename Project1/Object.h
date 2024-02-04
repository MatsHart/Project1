#pragma once
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Animator.h"
#include "PrimitiveMeshes.h"

using namespace std;

//Material struct to create different materials
struct Material {
	glm::vec3 ambient_color;
	glm::vec3 diffuse_color;
	glm::vec3 specular;
	float power = 1024;
};


class Object
{
public:
	// All needed variables to create a object
	const char* filePath;
	bool isPrimitive = false;
	const char* bmpPath;
	Material material = Material();
	Animator* animator = new Animator();
	vector<GLuint> indices;
	vector<glm::vec3> normals;
	vector<glm::vec3> vertices;
	vector<glm::vec3> colors;
	vector<glm::vec2> uvs;
	glm::mat4 model;
	glm::mat4 mv;
	GLuint texture_id;
	GLuint vao;

	Object();
	// constructor for object with bmp and obj file
	Object(const char*, const char*, glm::vec3 scale, glm::vec3 translate, glm::vec3 rotate, float angle);
	Object(const char*, const char*, glm::vec3 scale, glm::vec3 translate, glm::vec3 rotate, float angle, Animator* animator);
	//constructor with only a obj file
	Object(const char* filePath2, glm::vec3 scale, glm::vec3 translate, glm::vec3 rotate, float angle);

	// Primitive meshes
	Object(const PrimitiveMesh& primitiveMesh, glm::vec3 scale, glm::vec3 translate, glm::vec3 rotate, float angle);
	~Object() {
		
		//animator->~Animator();
	}

	void Render(glm::mat4 view, GLuint uniform_mv);


	void setAnimator(Animator*);
};

