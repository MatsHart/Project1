#include "WheelAnimator.h"

//Animates the car wheel to move in an direction
glm::mat4 WheelAnimator::Animate(glm::mat4 model) {
	model = glm::translate(model, glm::vec3(0, 0, 0.0075));
	return model;
}
