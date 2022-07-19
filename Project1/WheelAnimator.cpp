#include "WheelAnimator.h"


glm::mat4 WheelAnimator::Animate(glm::mat4 model) {
	//model = glm::translate(model, glm::vec3(0.00, 0.0,0.02));

	//glm::vec3 axis = glm::normalize(glm::vec3(model[0]));  // right vector
	//model = glm::rotate(model, glm::radians(1.f), glm::vec3(1, 0, 0));
	model = glm::rotate(model, 0.019f, glm::vec3(0.01f, 0.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.000, -0.01, 0));

	//model = glm::translate(model, glm::vec3(-1,-1,0));

	return model;
}