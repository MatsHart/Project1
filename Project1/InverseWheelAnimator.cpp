#include "InverseWheelAnimator.h"


//Animates the car wheel to move in an direction
glm::mat4 InverseWheelAnimator::Animate(glm::mat4 model) {
	//model = glm::translate(model, glm::vec3(0, 0, 0.0075));

	model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(10, 0, 0));
	return model;
}