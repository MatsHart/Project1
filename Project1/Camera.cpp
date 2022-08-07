#include "Camera.h"

Camera::Camera() : Camera::Camera(800,600){
	rotateX = 0.5;
	translateY = -1.5f;
}

Camera::Camera(const int WIDTH, const int HEIGHT) {
	standardView = glm::lookAt(
		glm::vec3(0.0, 1.0, 8.0),  // eye
		glm::vec3(0.0, 0.5, 0.0),  // center
		glm::vec3(0.0, 1.0, 0.0));  // up

	standardProjection = glm::perspective(
		glm::radians(45.0f),
		1.0f * WIDTH / HEIGHT, 0.1f,
		200.0f);
	translateX = -5;
	translateY = -5;
	translateZ = 9;
	standardView = glm::translate(standardView, glm::vec3(translateX, translateY, translateZ));

	rotateX = 0.21439f;
	rotateY = -2.439f;
	rotateZ = 0.0618128f;

}

Camera::Camera(glm::mat4 view, glm::mat4 projection) {
	this->standardView = view;
	this->standardProjection = projection;

	translateX = -3.2;
	translateY = 0;
	translateZ = 6.9;
	standardView = glm::translate(standardView, glm::vec3(translateX, translateY, translateZ));

	rotateX = 0;
	rotateY = -2.6;
	rotateZ = 0;
}

// Move player forward based upon the rotation sin is used for x and cos for z movement
void Camera::Forward() {
	translateX += -sin(rotateY) * speed;
	translateZ += cos(rotateY) * speed;
}
// Move player backwards based upon the rotation sin is used for x and cos for z movement
void Camera::Backwards() {
	translateX -= -sin(rotateY) * speed;
	translateZ -= cos(rotateY) * speed;
}
// Move player left based upon the rotation sin is used for x and cos for z movement
// remove 1.55 from the rotateY, because quarter rotation
void Camera::Left() {
	translateX += -sin(rotateY - 1.55) * speed;
	translateZ += cos(rotateY - 1.55) * speed;
}
// Move player right based upon the rotation sin is used for x and cos for z movement
// remove 1.55 from the rotateY, because quarter rotation
void Camera::Right() {
	translateX -= -sin(rotateY - 1.55) * speed;
	translateZ -= cos(rotateY - 1.55) * speed;
}
// change x rotation to look down
void Camera::LookDown() {
	if (rotateX > 6.2f && rotateX < 6.4f)
		rotateX -= 6.2f;
	rotateX += keyrotspeed;
}
// change x rotation to look up
void Camera::LookUp() {
	if (rotateX > -0.1f && rotateX < 0.1f)
		rotateX += 6.3f;
	rotateX -= keyrotspeed;
}
// change y rotation to look left
void Camera::LookLeft() {
	//Change 
	if (rotateY > -0.1f && rotateY < 0.1f)
		rotateY += 6.2f;
	rotateY -= keyrotspeed;
	std::cout << rotateY << std::endl;
}
// change y rotation to look right
void Camera::LookRight() {
	if (rotateY > 6.2f && rotateY < 6.4f)
		rotateY -= 6.3f;
	rotateY += keyrotspeed;
}
// translate y so player cam goes up
void Camera::Up() {
	translateY += speed;
}
// translate y so player cam goes down
void Camera::Down() {
	translateY -= speed;
}
//Handle mouse movement
void Camera::mouseMovemnt(int x, int y) {
	// Prevents massive jumps
	if (x - lastX > 100 || x - lastX < -100)
	{
		lastX = x;
		lastY = y;
	}
	if (y - lastY > 100 || y - lastY < -100)
	{
		lastX = x;
		lastY = y;
	}

	//Get the difference with last time
	float yaw = x - lastX;
	float pitch = y - lastY;
	lastX = x;
	lastY = y;
	std::cout << yaw << std::endl;

	// change the offset with the sensitivity
	yaw *= rotspeed;
	pitch *= rotspeed;

	//Add yaw offset to the rotate y 
	//Change rotx and rotz based upon the roty location
	rotateZ += pitch * sin(rotateY);
	rotateX += pitch * cos(rotateY);
	rotateY += yaw;
	if (rotateY > 6.2f && rotateY < 6.4f)
		rotateY -= 6.3f;
}

// Update the view and projection based on trans and rot data
void Camera::Update() {
	//translate camera view
	view = glm::translate(standardView, glm::vec3(translateX, translateY, translateZ));

	//projection matrix
	// Use standardProjection so data is reset
	// Use normal projection so rotY data is not lost
	projection = glm::rotate(standardProjection, rotateX, glm::vec3(1.0, 0.0, 0.0));
	projection = glm::rotate(projection, rotateY, glm::vec3(0.0, 1.0, 0.0));
	projection = glm::rotate(projection, rotateZ, glm::vec3(0.0, 0.0, 1.0));

}