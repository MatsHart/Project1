#include "Object.h"

Object::Object() {
	model = glm::mat4();
}

Object::Object(const char* filePath2, const char* bmpPath2, glm::vec3 scale, glm::vec3 translate, glm::vec3 rotate, float angle) {
	model = glm::mat4();
	filePath = filePath2;
	bmpPath = bmpPath2;
	model = glm::translate(model, translate);
	model = glm::rotate(model, angle, rotate);
	model = glm::scale(model, scale);
}

Object::Object(const char* filePath2, const char* bmpPath2, glm::vec3 scale, glm::vec3 translate, glm::vec3 rotate, float angle, Animator* animator) {
	model = glm::mat4();
	filePath = filePath2;
	bmpPath = bmpPath2;
	model = glm::translate(model, translate);
	model = glm::rotate(model, angle, rotate);
	model = glm::scale(model, scale);
	setAnimator(animator);
}

Object::Object(const char* filePath2, glm::vec3 scale, glm::vec3 translate, glm::vec3 rotate, float angle) {
	filePath = filePath2;
	model = glm::translate(model, translate);
	model = glm::rotate(model, glm::radians(angle), rotate);
	model = glm::scale(model, scale);
	bmpPath = nullptr;
}

// Render the object
void Object::Render(glm::mat4 view, GLuint uniform_mv) {
	//Animate
	model = animator->Animate_Execute(model);
	// Update mv
	mv = view * model;

	// Send mvp
	glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, glm::value_ptr(mv));

	glBindTexture(GL_TEXTURE_2D, texture_id);

	// Send vao
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glBindVertexArray(0);
}

// First delete the old animator to then add the new animator
void Object::setAnimator(Animator* animator) {
	delete this->animator;
	this->animator = animator;
}