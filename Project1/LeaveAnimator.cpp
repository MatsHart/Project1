#include "LeaveAnimator.h"
glm::mat4 LeaveAnimator::Animate(glm::mat4 model) {
	//model = glm::translate(model, glm::vec3(0, 0, 0.0075));

	//model = glm::scale(model, glm::vec3(0, 0, 0));
	model = glm::rotate(model, glm::radians(2.0f), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(5.0f), glm::vec3(0, 1, 0));
	return model;
}