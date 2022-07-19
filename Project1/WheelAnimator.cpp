#include "WheelAnimator.h"


glm::mat4 WheelAnimator::Animate(glm::mat4 model) {
	model = glm::translate(model, glm::vec3(0, 0, 0.0075));
	return model;
}
