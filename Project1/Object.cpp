#include "Object.h"

Object::Object() {
	model = glm::mat4();
}

Object::Object(const char* filePath2, const char* bmpPath2, glm::vec3 scale, glm::vec3 translate) {
	model = glm::mat4();
	Object::filePath = filePath2;
	Object::bmpPath = bmpPath2;
	model = glm::translate(model, translate);
	model = glm::scale(model, scale);


}

Object::Object(const char* filePath2, glm::vec3 scale, glm::vec3 translate) {
	Object::filePath = filePath2;
	model = glm::translate(model, translate);
	model = glm::scale(model, scale);
	Object::bmpPath = nullptr;

}

void Object::Animate(float speed, glm::mat4 view) {
	model = glm::rotate(model, speed, glm::vec3(0.0f, 1.0f, 0.0f));
	mv = view * model;
}