#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Camera
{
private:
	float rotateX = 0;
	float rotateY = 0;
	float rotateZ = 0;
	float translateX = 0;
	float translateY = 0;
	float translateZ = 0;


public:
	glm::mat4 view;
	glm::mat4 projection;
	Camera();
	Camera(glm::mat4, glm::mat4);
	Camera(const int, const int);


	void Forward();
	void Backwards();
	void Left();
	void Right();

	void LookUp();
	void LookDown();
	void LookLeft();
	void LookRight();

	void Up();
	void Down();

	void Update();
};

