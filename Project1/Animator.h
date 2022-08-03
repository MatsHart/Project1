#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Animator
{
public:
	//consatructor
	Animator() {}
	//deconstructor
	~Animator() {}

	// Is used to call the virtual animate function
	glm::mat4 Animate_Execute(glm::mat4 model) { return Animate(model); }

	//Virtual animate functions which every animating class needs to define itseld
	virtual glm::mat4 Animate(glm::mat4 model) { return model; }


};

