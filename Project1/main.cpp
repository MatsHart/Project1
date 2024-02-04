#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "glsl.h"
#include "objloader.h"
#include "texture.h"
#include "CubeGenerator.h"
#include "PrimitiveMeshes.h"


#include "Object.h"
#include "WheelAnimator.h"
#include "InverseWheelAnimator.h"
#include "RotateCupAnimator.h"
#include "LeaveAnimator.h"
#include "BodyAnimator.h"

using namespace std;


//--------------------------------------------------------------------------------
// Consts
//--------------------------------------------------------------------------------

const int WIDTH = 800, HEIGHT = 600;

const char* fragshader_name = "fragmentshader.fsh";
const char* vertexshader_name = "vertexshader.vsh";

unsigned const int DELTA_TIME = 10;


struct LightSource {
	glm::vec3 position;
};

//--------------------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------------------

// ID's
GLuint program_id;

// Uniform ID's
GLuint uniform_mv;
GLuint uniform_material_ambient;
GLuint uniform_material_diffuse;
GLuint uniform_material_specular;
GLuint uniform_material_power;
GLuint uniform_light_pos;
// Matrices

LightSource light;

vector<Object> objects;

// Primitive meshes
CubeMesh cubeMesh;
PyramidMesh pyramidMesh;
SphereMesh sphereMesh;
CylinderMesh cylinderMesh;
ConeMesh coneMesh;
DonutMesh donutMesh;

vector<Camera> cameras;
//Camera cameras[2];

int ActiveCameraInterval = 0;

//--------------------------------------------------------------------------------
// Initialize camera
//--------------------------------------------------------------------------------
void InitCameras() {

	//Walking mode camera
	glm::mat4 view = glm::lookAt(
		glm::vec3(0.0, 1.0, 8.0),  // eye
		glm::vec3(0.0, 0.5, 0.0),  // center
		glm::vec3(0.0, 1.0, 0.0));  // up

	glm::mat4 projection = glm::perspective(
		glm::radians(45.0f),
		1.0f * WIDTH / HEIGHT, 0.1f,
		200.0f);

	//cameras.push_back(Camera(view, projection, WIDTH, HEIGHT));
	cameras.push_back(Camera(view, projection));
	//cameras[0] = (Camera(view, projection));

	//overview camera
	//cameras[1] = Camera(WIDTH, HEIGHT);
	cameras.push_back(Camera(WIDTH, HEIGHT));
}

//--------------------------------------------------------------------------------
// Rendering
//--------------------------------------------------------------------------------
void Render() {
	cameras[ActiveCameraInterval].Update();
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Attach to program_id
	glUseProgram(program_id);

	// For every object call the render method
	for (int i = 0; i < objects.size(); i++) {
		objects[i].Render(cameras[ActiveCameraInterval].view, uniform_mv);
	}
	glutSwapBuffers();
}

//------------------------------------------------------------
// void Render(int n)
// Render method that is called by the timer function
//------------------------------------------------------------
void Render(int n) {
	Render();
	glutTimerFunc(DELTA_TIME, Render, 0);
}

//--------------------------------------------------------------------------------
// Create objects
// 
// Want to change scale, transform or rotation
// 
// First vec3 is Scale
// Second vec3 is Transform
// Third vec3 is Rotate
//--------------------------------------------------------------------------------
void createObjects() {
	////car body
	objects.push_back(Object("Objects/carNoTires.obj", "Textures/metal.bmp", glm::vec3(1.0, 1.0, 1.0), glm::vec3(0, 0, 0), glm::vec3(0.0, 1.0, 0.0), 0, new BodyAnimator()));

	//tire tire Left back 
	//objects.push_back(Object("Objects/Tire.obj", "Textures/uvtemplate.bmp", glm::vec3(1.0, 1.0, 1.0), glm::vec3(1, 3.5, -0.7), glm::vec3(0.0, 0.0, 1.0), 3.14f, new InverseWheelAnimator()));
	objects.push_back(Object("Objects/Tire.obj", "Textures/rubber.bmp", glm::vec3(1.0, 1.0, 1.0), glm::vec3(1, -0.5, -0.7), glm::vec3(0.0, 0.0, 1.0), 3.14f, new InverseWheelAnimator()));

	//tire tire left front
	objects.push_back(Object("Objects/Tire.obj", "Textures/rubber.bmp", glm::vec3(1.0, 1.0, 1.0), glm::vec3(1, -0.5, 1.8), glm::vec3(0.0, 0.0, 1.0), 3.14f, new InverseWheelAnimator()));

	//tire tire Right back 
	objects.push_back(Object("Objects/Tire.obj", "Textures/rubber.bmp", glm::vec3(1.0, 1.0, 1.0), glm::vec3(-0.9, -0.5, -0.7), glm::vec3(0.0, 0.0, 1.0), 0, new WheelAnimator()));

	//tire tire Right front
	objects.push_back(Object("Objects/Tire.obj", "Textures/rubber.bmp", glm::vec3(1.0, 1.0, 1.0), glm::vec3(-0.9, -0.5, 1.8), glm::vec3(0.0, 0.0, 1.0), 0, new WheelAnimator()));

	// Road
	objects.push_back(Object("Objects/box.obj", "Textures/brick.bmp", glm::vec3(10, 0.1, 40), glm::vec3(1, -1.2, 15), glm::vec3(0.0, 0.0, 1.0), 0));

	//Lantern
	objects.push_back(Object("Objects/Lightpost.obj", "Textures/metal.bmp", glm::vec3(0.6, 0.5, 0.6), glm::vec3(-2.9, -1.2, -3), glm::vec3(0.0, 0.0, 1.0), 0));
	objects.push_back(Object("Objects/Lightpost.obj", "Textures/metal.bmp", glm::vec3(0.6, 0.5, 0.6), glm::vec3(-2.9, -1.2, 34), glm::vec3(0.0, 0.0, 1.0), 0));

	//elecbox
	objects.push_back(Object("Objects/Elecbox.obj", "Textures/metal.bmp", glm::vec3(1, 1, 0.6), glm::vec3(-10, -1, 7.6), glm::vec3(0.0, 0.0, 1.0), 0));

	//plants
	objects.push_back(Object("Objects/plants.obj", "Textures/wood.bmp", glm::vec3(1, 0.8, 0.6), glm::vec3(-11, -1, 10), glm::vec3(0.0, 0.0, 1.0), 0));
	objects.push_back(Object("Objects/cylinder32.obj", "Textures/wood.bmp", glm::vec3(0.3, 4, 0.3), glm::vec3(-5, -1, 10), glm::vec3(0.0, 0.0, 1.0), 0));
	objects.push_back(Object("Objects/sphere.obj", "Textures/leaves.bmp", glm::vec3(1, 1, 1), glm::vec3(-5, 4, 10), glm::vec3(0.0, 0.0, 1.0), 0, new LeaveAnimator()));


	objects.push_back(Object("Objects/plants.obj", "Textures/wood.bmp", glm::vec3(1, 0.8, 0.6), glm::vec3(-11, -1, 22), glm::vec3(0.0, 0.0, 1.0), 0));
	objects.push_back(Object("Objects/cylinder32.obj", "Textures/wood.bmp", glm::vec3(0.3, 4, 0.3), glm::vec3(-5, -1, 22), glm::vec3(0.0, 0.0, 1.0), 0));
	objects.push_back(Object("Objects/sphere.obj", "Textures/leaves.bmp", glm::vec3(1, 1, 1), glm::vec3(-5, 4, 22), glm::vec3(0.0, 0.0, 1.0), 0, new LeaveAnimator()));


	//teapot
	objects.push_back(Object("Objects/teapot.obj", "Textures/yellowbrk.bmp", glm::vec3(1, 1, 1), glm::vec3(-7, -1, 18), glm::vec3(0.0, 0.0, 1.0), 0, new RotateCupAnimator()));
	objects.push_back(Object("Objects/teapot.obj", "Textures/yellowbrk.bmp", glm::vec3(1, 1, 1), glm::vec3(-7, -1, 13), glm::vec3(0.0, 0.0, 1.0), 0, new RotateCupAnimator()));

	//houses


	//1
	// path
	objects.push_back(Object("Objects/box.obj", "Textures/yellowbrk.bmp", glm::vec3(10, 0.1, 6), glm::vec3(-9, -1.2, 1), glm::vec3(0.0, 0.0, 1.0), 0));
	//block
	objects.push_back(Object("Objects/box.obj", "Textures/brick.bmp", glm::vec3(8.0, 6.0, 6.0), glm::vec3(-15, -1, 1), glm::vec3(0.0, 0.0, 1.0), 0));
	//roof
	objects.push_back(Object("Objects/roof.obj", "Textures/roof2.bmp", glm::vec3(0.55, 1.0, 1.8), glm::vec3(-15, 3, -1.45), glm::vec3(0.0, 2, 0.0), 29.85));
	//door
	objects.push_back(Object("Objects/door.obj", "Textures/bluewood.bmp", glm::vec3(1, 0.7, 0.7), glm::vec3(-11.05, -1, 1), glm::vec3(0.0, 2, 0.0), 0));


	//2
	// path
	objects.push_back(Object("Objects/box.obj", "Textures/yellowbrk.bmp", glm::vec3(10, 0.1, 1), glm::vec3(-9, -1.2, 4.5), glm::vec3(0.0, 0.0, 1.0), 0));
	// gravel
	objects.push_back(Object("Objects/box.obj", "Textures/gravel.bmp", glm::vec3(10, 0.1, 5.2), glm::vec3(-9, -1.2, 7.5), glm::vec3(0.0, 0.0, 1.0), 0));
	//block
	objects.push_back(Object("Objects/box.obj", "Textures/brick.bmp", glm::vec3(8.0, 6.0, 6.0), glm::vec3(-15, -1, 7), glm::vec3(0.0, 0.0, 1.0), 0));
	//roof
	objects.push_back(Object("Objects/roof.obj", "Textures/roof2.bmp", glm::vec3(0.55, 1.0, 1.8), glm::vec3(-15, 3, 4.45), glm::vec3(0.0, 2, 0.0), 29.85));
	//Chimney
	objects.push_back(Object("Objects/Chimney.obj", "Textures/brick.bmp", glm::vec3(0.5, 0.4, 0.5), glm::vec3(-15, 8, 4.45), glm::vec3(0.0, 0, 1.0), 0));
	//door
	objects.push_back(Object("Objects/door.obj", "Textures/bluewood.bmp", glm::vec3(1, 0.7, 0.7), glm::vec3(-11.05, -1, 4.3), glm::vec3(0.0, 2, 0.0), 0));


	//3
	// gravel
	objects.push_back(Object("Objects/box.obj", "Textures/gravel.bmp", glm::vec3(10, 0.1, 5.2), glm::vec3(-9, -1.2, 12.5), glm::vec3(0.0, 0.0, 1.0), 0));
	// path
	objects.push_back(Object("Objects/box.obj", "Textures/yellowbrk.bmp", glm::vec3(10, 0.1, 1.8), glm::vec3(-9, -1.2, 16), glm::vec3(0.0, 0.0, 1.0), 0));
	//block
	objects.push_back(Object("Objects/box.obj", "Textures/brick.bmp", glm::vec3(8.0, 6.0, 6.0), glm::vec3(-15, -1, 13), glm::vec3(0.0, 0.0, 1.0), 0));
	//roof
	objects.push_back(Object("Objects/roof.obj", "Textures/roof2.bmp", glm::vec3(0.55, 1.0, 1.8), glm::vec3(-15, 3, 9.45), glm::vec3(0.0, 2, 0.0), 29.85));
	//door
	objects.push_back(Object("Objects/door.obj", "Textures/bluewood.bmp", glm::vec3(1, 0.7, 0.7), glm::vec3(-11.05, -1, 14.3), glm::vec3(0.0, 2, 0.0), 0));

	//pillars
	objects.push_back(Object("Objects/SimplePole.obj", "Textures/brick.bmp", glm::vec3(0.3, 0.3, 0.3), glm::vec3(-4.4, -1.2, 15), glm::vec3(0.0, 0.0, 1.0), 0));
	objects.push_back(Object("Objects/SimplePole.obj", "Textures/brick.bmp", glm::vec3(0.3, 0.3, 0.3), glm::vec3(-4.4, -1.2, 17), glm::vec3(0.0, 0.0, 1.0), 0));

	//4
	// gravel
	objects.push_back(Object("Objects/box.obj", "Textures/gravel.bmp", glm::vec3(10, 0.1, 5.2), glm::vec3(-9, -1.2, 19.5), glm::vec3(0.0, 0.0, 1.0), 0));
	//block
	objects.push_back(Object("Objects/box.obj", "Textures/brick.bmp", glm::vec3(8.0, 6.0, 6.0), glm::vec3(-15, -1, 19), glm::vec3(0.0, 0.0, 1.0), 0));
	//roof
	objects.push_back(Object("Objects/roof.obj", "Textures/roof2.bmp", glm::vec3(0.55, 1.0, 1.8), glm::vec3(-15, 3, 14.45), glm::vec3(0.0, 2, 0.0), 29.85));
	//Chimney
	objects.push_back(Object("Objects/Chimney.obj", "Textures/brick.bmp", glm::vec3(0.5, 0.4, 0.5), glm::vec3(-15, 8, 14.45), glm::vec3(0.0, 0, 1.0), 0));
	//door
	objects.push_back(Object("Objects/door.obj", "Textures/bluewood.bmp", glm::vec3(1, 0.7, 0.7), glm::vec3(-11.05, -1, 18.3), glm::vec3(0.0, 2, 0.0), 0));


	//5
	// gravel
	objects.push_back(Object("Objects/box.obj", "Textures/gravel.bmp", glm::vec3(10, 0.1, 5.2), glm::vec3(-9, -1.2, 24.5), glm::vec3(0.0, 0.0, 1.0), 0));
	// path
	objects.push_back(Object("Objects/box.obj", "Textures/yellowbrk.bmp", glm::vec3(10, 0.1, 1), glm::vec3(-9, -1.2, 27.5), glm::vec3(0.0, 0.0, 1.0), 0));
	//block
	objects.push_back(Object("Objects/box.obj", "Textures/brick.bmp", glm::vec3(8.0, 6.0, 6.0), glm::vec3(-15, -1, 25), glm::vec3(0.0, 0.0, 1.0), 0));
	//roof
	objects.push_back(Object("Objects/roof.obj", "Textures/roof2.bmp", glm::vec3(0.55, 1.0, 1.8), glm::vec3(-15, 3, 19.45), glm::vec3(0.0, 2, 0.0), 29.85));
	//door
	objects.push_back(Object("Objects/door.obj", "Textures/bluewood.bmp", glm::vec3(1, 0.7, 0.7), glm::vec3(-11.05, -1, 27.3), glm::vec3(0.0, 2, 0.0), 0));


	//6
	// path
	objects.push_back(Object("Objects/box.obj", "Textures/yellowbrk.bmp", glm::vec3(10, 0.1, 6), glm::vec3(-9, -1.2, 31), glm::vec3(0.0, 0.0, 1.0), 0));
	//block
	objects.push_back(Object("Objects/box.obj", "Textures/brick.bmp", glm::vec3(8.0, 6.0, 6.0), glm::vec3(-15, -1, 31), glm::vec3(0.0, 0.0, 1.0), 0));
	//roof
	objects.push_back(Object("Objects/roof.obj", "Textures/roof2.bmp", glm::vec3(0.55, 1.0, 1.8), glm::vec3(-15, 3, 24.45), glm::vec3(0.0, 2, 0.0), 29.85));
	objects.push_back(Object("Objects/roof.obj", "Textures/roof2.bmp", glm::vec3(0.55, 1.0, 1.8), glm::vec3(-15, 3, 28.45), glm::vec3(0.0, 2, 0.0), 29.85));
	//Chimney
	objects.push_back(Object("Objects/Chimney.obj", "Textures/brick.bmp", glm::vec3(0.5, 0.4, 0.5), glm::vec3(-15, 8, 24.45), glm::vec3(0.0, 0, 1.0), 0));
	//door
	objects.push_back(Object("Objects/door.obj", "Textures/bluewood.bmp", glm::vec3(1, 0.7, 0.7), glm::vec3(-11.05, -1, 29.3), glm::vec3(0.0, 2, 0.0), 0));

	// Primitive meshes Options: cubeMesh, pyramidMesh, sphereMesh, cylinderMesh, coneMesh, donutMesh
	objects.push_back(Object(cubeMesh, glm::vec3(1.0, 1.0, 1.0), glm::vec3(-5, -1,29), glm::vec3(0.0, 1.0, 0.0), 0));
	objects.push_back(Object(pyramidMesh, glm::vec3(1.0, 1.0, 1.0), glm::vec3(-5, -1, 31), glm::vec3(0.0, 1.0, 0.0), 0));
	objects.push_back(Object(sphereMesh, glm::vec3(1.0, 1.0, 1.0), glm::vec3(-5, 0, 33), glm::vec3(0.0, 1.0, 0.0), 0));

}

//--------------------------------------------------------------------------------
// Init Matrices
//--------------------------------------------------------------------------------
void InitMatrices() {

	cameras[ActiveCameraInterval].Update();

	for (int i = 0; i < objects.size(); i++) {
		objects[i].mv = cameras[ActiveCameraInterval].view * objects[i].model * cameras[ActiveCameraInterval].projection;
	}
}

//------------------------------------------------------------
// void InitBuffers()
// Allocates and fills buffers
//------------------------------------------------------------
void InitBuffers() {
	GLuint position_id, normal_id, uv_id;
	GLuint vbo_vertices, vbo_normals, vbo_uvs, ebo_indices;

	// Retrieve attribute locations
	position_id = glGetAttribLocation(program_id, "position");
	normal_id = glGetAttribLocation(program_id, "normal");
	uv_id = glGetAttribLocation(program_id, "uv");

	// Retrieve uniform locations
	uniform_mv = glGetUniformLocation(program_id, "mv");
	GLuint uniform_proj = glGetUniformLocation(program_id, "projection");
	uniform_light_pos = glGetUniformLocation(program_id, "light_pos");
	uniform_material_ambient = glGetUniformLocation(program_id, "mat_ambient");
	uniform_material_diffuse = glGetUniformLocation(program_id, "mat_diffuse");
	uniform_material_power = glGetUniformLocation(program_id, "mat_power");
	uniform_material_specular = glGetUniformLocation(program_id, "mat_specular");

	for (int i = 0; i < objects.size(); i++) {
		glGenVertexArrays(1, &objects[i].vao);
		glBindVertexArray(objects[i].vao);

		// Vertices
		glGenBuffers(1, &vbo_vertices);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
		glBufferData(GL_ARRAY_BUFFER, objects[i].vertices.size() * sizeof(glm::vec3), objects[i].vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(position_id, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(position_id);

		if (!objects[i].isPrimitive || objects[i].normals.size() > 0) {
			// Normals
			glGenBuffers(1, &vbo_normals);
			glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
			glBufferData(GL_ARRAY_BUFFER, objects[i].normals.size() * sizeof(glm::vec3), objects[i].normals.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(normal_id, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
			glEnableVertexAttribArray(normal_id);
		}

		if (!objects[i].isPrimitive || objects[i].uvs.size() > 0) {
			// UVs
			glGenBuffers(1, &vbo_uvs);
			glBindBuffer(GL_ARRAY_BUFFER, vbo_uvs);
			glBufferData(GL_ARRAY_BUFFER, objects[i].uvs.size() * sizeof(glm::vec2), objects[i].uvs.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(uv_id, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
			glEnableVertexAttribArray(uv_id);
		}

		if (objects[i].isPrimitive && !objects[i].indices.empty()) {
			// Indices
			glGenBuffers(1, &ebo_indices);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_indices);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, objects[i].indices.size() * sizeof(GLuint), objects[i].indices.data(), GL_STATIC_DRAW);
		}

		glBindVertexArray(0); // Unbind VAO

		glUniform3fv(uniform_light_pos, 1, glm::value_ptr(light.position));
		glUniform3fv(uniform_material_ambient, 1, glm::value_ptr(objects[i].material.ambient_color));
		glUniform3fv(uniform_material_diffuse, 1, glm::value_ptr(objects[i].material.diffuse_color));
		glUniform1f(uniform_material_power, objects[i].material.power);
		glUniform3fv(uniform_material_specular, 1, glm::value_ptr(objects[i].material.specular));
		// Define model

		objects[i].mv = cameras[ActiveCameraInterval].view * objects[i].model * cameras[ActiveCameraInterval].projection;

		// Send mvp
		glUseProgram(program_id);
		glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, glm::value_ptr(objects[i].mv));
		glUniformMatrix4fv(uniform_proj, 1, GL_FALSE, glm::value_ptr(cameras[ActiveCameraInterval].projection));

		// No need to bind material properties here; they should be bound when drawing each object.
	}
}






void updateBuffers() {

	GLuint uniform_proj = glGetUniformLocation(program_id, "projection");
	for (int i = 0; i < objects.size(); i++) {

		objects[i].mv = cameras[ActiveCameraInterval].view * objects[i].model * cameras[ActiveCameraInterval].projection;

		// Send mvp
		glUseProgram(program_id);
		glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, glm::value_ptr(objects[i].mv));
		glUniformMatrix4fv(uniform_proj, 1, GL_FALSE, glm::value_ptr(cameras[ActiveCameraInterval].projection));

	}
}

//------------------------------------------------------------
// Add all keyboard handlers
//------------------------------------------------------------

void keyboardHandler(unsigned char key, int a, int b) {
	switch (key) {
		//Esc pressed close the application
	case 27:
		glutExit();
		break;
	case 119: //W
	case 87:
		cameras[ActiveCameraInterval].Forward();
		break;
	case 97: //A
	case 65:
		cameras[ActiveCameraInterval].Left();
		break;
	case 115: //S
	case 83:
		cameras[ActiveCameraInterval].Backwards();
		break;
	case 100: //D
	case 68:
		cameras[ActiveCameraInterval].Right();
		break;
	case 73: // I
	case 105:
		cameras[ActiveCameraInterval].LookUp();
		break;
	case 74: //J
	case 106:
		cameras[ActiveCameraInterval].LookLeft();
		break;
	case 75: //K
	case 107:
		cameras[ActiveCameraInterval].LookDown();
		break;
	case 76: //L
	case 108:
		cameras[ActiveCameraInterval].LookRight();
		break;
	case 81: // Q
	case 113:
		//TO MOVE UP AND DOWN DRONE MODE

		if (ActiveCameraInterval == 1) {
			cameras[ActiveCameraInterval].Up();
		}
		break;
	case 69: // E
	case 101:
		//TO MOVE UP AND DOWN DRONE MODE

		if (ActiveCameraInterval == 1) {
			cameras[ActiveCameraInterval].Down();
		}
		break;
		//V Switch between walk and drone mode
	case 118:
	case 86:
		ActiveCameraInterval = (ActiveCameraInterval + 1) % cameras.size();
		if (ActiveCameraInterval == 1) {
			cameras[1] = Camera();
		}
		break;
	}
	InitMatrices();
	updateBuffers();
}
int c = 0;
//------------------------------------------------------------
// call mousemovent
//------------------------------------------------------------
void mouseHandler(int mx, int my) {
	cameras[ActiveCameraInterval].mouseMovemnt(mx, my);
	// prevents being updated to fast.
	if (c > 10){
		InitMatrices();
		updateBuffers();
		c = 0;
	}
	c++;
}

//------------------------------------------------------------
// void InitGlutGlew(int argc, char **argv)
// Initializes Glut and Glew
//------------------------------------------------------------
void InitGlutGlew(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Hello OpenGL");
	glutDisplayFunc(Render);
	glutKeyboardFunc(keyboardHandler);
	glutMotionFunc(mouseHandler);
	glutTimerFunc(DELTA_TIME, Render, 0);

	glewInit();
}

//------------------------------------------------------------
// void InitShaders()
// Initializes the fragmentshader and vertexshader
//------------------------------------------------------------
void InitShaders() {
	char* vertexshader = glsl::readFile(vertexshader_name);
	GLuint vsh_id = glsl::makeVertexShader(vertexshader);

	char* fragshader = glsl::readFile(fragshader_name);
	GLuint fsh_id = glsl::makeFragmentShader(fragshader);

	program_id = glsl::makeShaderProgram(vsh_id, fsh_id);
}

//------------------------------------------------------------
// Init objects
//------------------------------------------------------------
void InitObjects() {

	for (int i = 0; i < objects.size(); i++) {
		try {
			if (objects[i].filePath != nullptr) {
				bool res = loadOBJ(objects[i].filePath, objects[i].vertices, objects[i].uvs, objects[i].normals);
				if (!res) {
					// Handle loading failure for the OBJ file here (e.g., log an error).
				}
			}

			if (objects[i].bmpPath != nullptr) {
				objects[i].texture_id = loadBMP(objects[i].bmpPath);
				if (objects[i].texture_id == -1) {
					// Handle loading failure for the BMP texture here (e.g., log an error).
				}
			}
		}
		catch (const std::exception& e) {
			// Handle any exceptions thrown during resource loading (e.g., log the exception message).
		}
	}
}

//------------------------------------------------------------
// Init lights
//------------------------------------------------------------
void InitLight() {
	light.position = glm::vec3(4.0, 4.0, 4.0);
}

// Main object
int main(int argc, char** argv) {

	InitGlutGlew(argc, argv);
	createObjects();
	InitCameras();
	InitShaders();
	InitMatrices();

	InitObjects();
	InitLight();
	InitBuffers();


	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	// Main loop
	glutMainLoop();

	return 0;
}
