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

#include "Object.h"

#define objectsSize sizeof(objects) / sizeof(*objects);

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
//GLuint uniform_light_pos;

// Matrices

glm::mat4 projection;

LightSource light;

vector<Object> objectList;

Object objects[2];

bool firstInitMatric = true;

//vector<Camera> cameras;
Camera cameras[2];

int ActiveCameraInterval = 1;

void InitCameras() {
	glm::mat4 view = glm::lookAt(
		glm::vec3(0.0, 1.0, 8.0),  // eye
		glm::vec3(0.0, 0.5, 0.0),  // center
		glm::vec3(0.0, 1.0, 0.0));  // up

	glm::mat4 projection = glm::perspective(
		glm::radians(45.0f),
		1.0f * WIDTH / HEIGHT, 0.1f,
		20.0f);

	//cameras.push_back(Camera(view, projection, WIDTH, HEIGHT));
	cameras[0] = (Camera(view, projection));
	cameras[1] = Camera(WIDTH, HEIGHT);
}
//--------------------------------------------------------------------------------
// Mesh variables
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
// Keyboard handling
//--------------------------------------------------------------------------------




//--------------------------------------------------------------------------------
// Rendering
//--------------------------------------------------------------------------------

void Render() {
	cameras[ActiveCameraInterval].Update();
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Do transformation
	objects[0].model = glm::rotate(objects[0].model, 0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
	objects[1].model = glm::rotate(objects[1].model, 0.01f, glm::vec3(0.0f, 1.0f, 0.0f));

	// Attach to program_id
	glUseProgram(program_id);


	for (int i = 0; i < 2; i++) {
		objects[i].mv = cameras[ActiveCameraInterval].view * objects[i].model;

		// Send mvp
		glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, glm::value_ptr(objects[i].mv));

		glBindTexture(GL_TEXTURE_2D, objects[i].texture_id);



		// Send vao
		glBindVertexArray(objects[i].vao);
		glDrawArrays(GL_TRIANGLES, 0, objects[i].vertices.size());
		glBindVertexArray(0);

	}
	glutSwapBuffers();
}


void createObjects() {
	objectList.push_back(Object());
	//objects[0] = Object("Objects/car.obj", "Textures/Yellobrk.bmp", glm::vec3(1, 1, 1) , glm::vec3(-4.0, -0.25, -3.0));
	//objects[1] = Object("Objects/torus.obj", "Textures/uvtemplate.bmp", glm::vec3(1, 1, 1), glm::vec3(-4.0, -0.25, -2.0));

	objects[0] = Object("Objects/carNoTires.obj", "Textures/Yellobrk.bmp", glm::vec3(0.0, -1.0, -3.0), glm::vec3(2.5, 2.5, 2.5));

	objects[1] = Object("Objects/Tire.obj", "Textures/Yellobrk.bmp", glm::vec3(0.0, 3.0, -3.0), glm::vec3(2.5, 1.5, 2.5));
}

//------------------------------------------------------------
// void Render(int n)
// Render method that is called by the timer function
//------------------------------------------------------------

void Render(int n) {
	Render();
	glutTimerFunc(DELTA_TIME, Render, 0);
}

//  Only empty the model mat4 on first run
void createEmptyMat4(int i) {
	objects[i].model = glm::mat4();
}

void InitMatrices(int i) {
// Prevents the animation from stopping
	if (firstInitMatric)
		createEmptyMat4(i);

	objects[i].mv = cameras[ActiveCameraInterval].view * objects[i].model * cameras[ActiveCameraInterval].projection;
}


void InitMatrices() {

	cameras[ActiveCameraInterval].Update();

	for (int i = 0; i < sizeof(objects) / sizeof(*objects); i++) {
		InitMatrices(i);
	}
	firstInitMatric = false;
}

//------------------------------------------------------------
// void InitBuffers()
// Allocates and fills buffers
//------------------------------------------------------------

void InitBuffers() {
	GLuint position_id, color_id;
	GLuint vbo_vertices, vbo_colors;
	GLuint vbo_normals, vbo_uvs;

	GLuint uv_id = glGetAttribLocation(program_id, "uv");

	// Get vertex attributes
	position_id = glGetAttribLocation(program_id, "position");
	color_id = glGetAttribLocation(program_id, "colour");
	GLuint normal_id = glGetAttribLocation(program_id, "normal");

	// Make uniform vars
	uniform_mv = glGetUniformLocation(program_id, "mv");
	GLuint uniform_proj = glGetUniformLocation(program_id, "projection");
	uniform_light_pos = glGetUniformLocation(program_id, "light_pos");
	uniform_material_ambient = glGetUniformLocation(program_id,
		"mat_ambient");
	uniform_material_diffuse = glGetUniformLocation(program_id,
		"mat_diffuse");
	uniform_material_power = glGetUniformLocation(program_id,
		"mat_power");


	int size = objectsSize;

	for (int i = 0; i < (int)sizeof(objects) / sizeof(*objects); i++) {

		glGenBuffers(1, &vbo_normals);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
		glBufferData(GL_ARRAY_BUFFER,
			objects[i].normals.size() * sizeof(glm::vec3),
			&objects[i].normals[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &vbo_vertices);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
		glBufferData(GL_ARRAY_BUFFER,
			objects[i].vertices.size() * sizeof(glm::vec3), &objects[i].vertices[0],
			GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &vbo_uvs);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_uvs);
		glBufferData(GL_ARRAY_BUFFER, objects[i].uvs.size() * sizeof(glm::vec2),
			&objects[i].uvs[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Allocate memory for vao
		glGenVertexArrays(1, &objects[i].vao);

		// Bind to vao
		glBindVertexArray(objects[i].vao);

		// Bind vertices to vao
		glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
		glVertexAttribPointer(position_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(position_id);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
		glVertexAttribPointer(normal_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(normal_id);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_uvs);
		glVertexAttribPointer(uv_id, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(uv_id);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Stop bind to vao
		glBindVertexArray(0);

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

	}


}
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
		ActiveCameraInterval = (ActiveCameraInterval + 1) % (sizeof(cameras) / sizeof(*cameras));
		//ActiveCameraInterval = (ActiveCameraInterval + 1) % cameras.size();

		if (ActiveCameraInterval == 1) {
			cameras[1] = Camera();
		}
		break;
	}
	InitMatrices();
	InitBuffers();
	Render();
}
//------------------------------------------------------------
// void InitGlutGlew(int argc, char **argv)
// Initializes Glut and Glew
//------------------------------------------------------------

void mouseHandler(int mx, int my) {
	cameras[ActiveCameraInterval].mouseMovemnt(mx, my);
	InitMatrices();
	InitBuffers();
	Render();
	//std::cout << "x" << mx << ", y" << my << std::endl;
}

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

void InitObjects() {
	for (int i = 0; i < 2; i++) {
		if (objects[i].filePath != nullptr)
			bool res = loadOBJ(objects[i].filePath, objects[i].vertices, objects[i].uvs, objects[i].normals);
		if (objects[i].bmpPath != nullptr)
			objects[i].texture_id = loadBMP(objects[i].bmpPath);
	}
}

//------------------------------------------------------------
// void InitMatrices()
// 
//------------------------------------------------------------



//DERK
//view matrix
//view = glm::lookAt(
//	glm::vec3(0.0, 1.0, 8.0),  // eye
//	glm::vec3(0.0, 0.5, 0.0),  // center
//	glm::vec3(0.0, 1.0, 0.0));  // up
//view = glm::translate(view, glm::vec3(translateX, translateY, translateZ));
//
////projection matrix
//projection = glm::perspective(
//	glm::radians(45.0f),
//	1.0f * WIDTH / HEIGHT, 0.1f,
//	20.0f);
//projection = glm::rotate(projection, rotateY, glm::vec3(0.0, 1.0, 0.0));
//projection = glm::rotate(projection, rotateX, glm::vec3(1.0, 0.0, 0.0));
//
//for (int i = 0; i < amountOfModels; i++)
//	mv[i] = view * model[i] * projection;



void InitLight() {
	light.position = glm::vec3(4.0, 4.0, 4.0);

	objects[0].material.ambient_color = glm::vec3(0.2, 0.2, 0.1);
	objects[0].material.diffuse_color = glm::vec3(0.5, 0.5, 0.3);
	objects[0].material.specular = glm::vec3(0.7, 0.7, 0.7);
	objects[0].material.power = 1024.0f;

	objects[1].material.ambient_color = glm::vec3(0.2, 0.2, 0.1);
	objects[1].material.diffuse_color = glm::vec3(1.0, 1.0, 1.0);
	objects[1].material.specular = glm::vec3(0.7, 0.7, 0.7);
	objects[1].material.power = 1024.0f;
}





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
