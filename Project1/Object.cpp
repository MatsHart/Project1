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

void Object::Render(glm::mat4 view, GLuint uniform_mv) {
	mv = view * model;

	// Send mvp
	glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, glm::value_ptr(mv));

	glBindTexture(GL_TEXTURE_2D, texture_id);



	// Send vao
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glBindVertexArray(0);
}