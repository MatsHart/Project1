#include "Object.h"

Object::Object() {

}

Object::Object(const char* filePath2, const char* bmpPath2, glm::vec3 scale, glm::vec3 translate) {
	Object::filePath = filePath2;
	Object::bmpPath = bmpPath2;
	model = glm::translate(model, translate);
	model = glm::scale(model, scale);

}

void Object::Animate(float speed, glm::mat4 view) {
	model = glm::rotate(model, speed, glm::vec3(0.0f, 1.0f, 0.0f));
	mv = view * model;
}