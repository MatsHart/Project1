#include "BodyAnimator.h"

// Animates the car body to move in one directions
glm::mat4 BodyAnimator::Animate(glm::mat4 model) {
	//model = glm::translate(model, glm::vec3(0.00, 0.0, 0.02));
	model = glm::rotate(model, 0.01f, glm::vec3(1.0f, 0.0f, 0.0f));
	return model;
}