#include "Object.h"

// --------------------------------------------------
// 
// Object class is meant for all objects shown in the scene. It works for both primitive as obj files.
// 
// The order for translating a Object is always the same: Scale, Translate, Rotate
// --------------------------------------------------


Object::Object() {
	model = glm::mat4();
}

// Init for Object and bmp no animator
Object::Object(const char* filePath2, const char* bmpPath2, glm::vec3 scale, glm::vec3 translate, glm::vec3 rotate, float angle) {
	model = glm::mat4();
	filePath = filePath2;
	bmpPath = bmpPath2;
	model = glm::translate(model, translate);
	model = glm::rotate(model, angle, rotate);
	model = glm::scale(model, scale);
}

// Init for object with bmp and animator
Object::Object(const char* filePath2, const char* bmpPath2, glm::vec3 scale, glm::vec3 translate, glm::vec3 rotate, float angle, Animator* animator) {
	model = glm::mat4();
	filePath = filePath2;
	bmpPath = bmpPath2;
	model = glm::translate(model, translate);
	model = glm::rotate(model, angle, rotate);
	model = glm::scale(model, scale);
	setAnimator(animator);
}

// Init for Object with no bmp
Object::Object(const char* filePath2, glm::vec3 scale, glm::vec3 translate, glm::vec3 rotate, float angle) {
	filePath = filePath2;
	model = glm::translate(model, translate);
	model = glm::rotate(model, glm::radians(angle), rotate);
	model = glm::scale(model, scale);
	bmpPath = nullptr;
}

// Init for primitve meshes
Object::Object(const PrimitiveMesh& primitiveMesh, glm::vec3 scale, glm::vec3 translate, glm::vec3 rotate, float angle) {
	vertices = primitiveMesh.GetVertices();
	indices = primitiveMesh.GetIndices();
	// Setup the model matrix with provided transformation parameters
	model = glm::mat4(1.0f); // Initialize to identity matrix
	model = glm::translate(model, translate);
	model = glm::rotate(model, glm::radians(angle), rotate);
	model = glm::scale(model, scale);
	// Assume texture and animator are set later or default to null/none
	bmpPath = nullptr;
	animator = nullptr;
	isPrimitive = true;
	// Initialize OpenGL buffers (VBO, EBO, VAO) here or in a separate setup function
}


// Render the object
void Object::Render(glm::mat4 view, GLuint uniform_mv) {
	// Apply animation transformation
	if (animator) {
		model = animator->Animate_Execute(model);
	}
	mv = view * model;
	glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, glm::value_ptr(mv));

	glBindTexture(GL_TEXTURE_2D, texture_id);
	glBindVertexArray(vao);

	// Determine drawing mode based on the presence of indices
	if (!indices.empty()) {
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}
	else {
		glDrawArrays(GL_TRIANGLES, 0, vertices.size()); // Assuming each vertex is a vec3
	}

	glBindVertexArray(0);
}


// First delete the old animator to then add the new animator
void Object::setAnimator(Animator* animator) {
	delete this->animator;
	this->animator = animator;
}