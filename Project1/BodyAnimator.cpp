#include "BodyAnimator.h"

// Animates the car body to move in one directions
glm::mat4 BodyAnimator::Animate(glm::mat4 model) {
	if (count >= 500) {
		count = -1;
		model = glm::translate(model, glm::vec3(0, 0, -30));
	}
	else {
		model = glm::translate(model, glm::vec3(0.00, 0.0, 0.06));
	}
	count++;
	return model;
}