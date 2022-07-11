#include "WheelAnimator.h"


glm::mat4 WheelAnimator::Animate(glm::mat4 model) {
	model = glm::translate(model, glm::vec3(0.00, 0.0,0.05));

	//glm::vec3 axis = glm::normalize(glm::vec3(model[0]));  // right vector
	//model = glm::rotate(model, glm::radians(1.f), glm::vec3(1, 0, 0));
	//model = glm::rotate(model, 0.01f, glm::vec3(1.0f, 0.0f, 0.0f));

	return model;
}