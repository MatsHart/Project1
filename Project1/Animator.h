#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Animator
{
public:
	Animator() {}
	~Animator() {}

	glm::mat4 Animate_Execute(glm::mat4 model) { return Animate(model); }

	virtual glm::mat4 Animate(glm::mat4 model) { return model; }


};

