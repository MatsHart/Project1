#include "WheelAnimator.h"

//Animates the car wheel to move in an direction
glm::mat4 WheelAnimator::Animate(glm::mat4 model) {
	if (count >= 500) {
		model = glm::rotate(model, glm::radians(((count - 1.0f) * rotate)), glm::vec3(1, 0, 0));
		model = glm::translate(model, glm::vec3(0, 0, -30));
		count = -1;
	}
	else {
		if (count > 0) {
			model = glm::rotate(model, glm::radians(((count - 1.0f) * rotate)), glm::vec3(1, 0, 0));
		}
		model = glm::translate(model, glm::vec3(0.00, 0.0, 0.06));
		model = glm::rotate(model, glm::radians(count * (-1.0f * rotate)), glm::vec3(1, 0, 0));
	}
	count++;
	return model;
}
