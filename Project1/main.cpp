#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

glm::mat4 view, projection;

LightSource light;

Object objects[2];

//--------------------------------------------------------------------------------
// Mesh variables
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
// Keyboard handling
//--------------------------------------------------------------------------------

void keyboardHandler(unsigned char key, int a, int b) {
	switch (key) {
	case 27:
		glutExit();
		break;
	case 119:
		glutExit();
			break;
	case 97:
		glutExit();
		break;
	case 115:
		glutExit();
		break;
	case 100:
		glutExit();
		break;
	}
}


//--------------------------------------------------------------------------------
// Rendering
//--------------------------------------------------------------------------------

void Render() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Do transformation
	objects[0].model = glm::rotate(objects[0].model, 0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
	objects[1].model = glm::rotate(objects[1].model, 0.01f, glm::vec3(0.0f, 1.0f, 0.0f));

	// Attach to program_id
	glUseProgram(program_id);


	for (int i = 0; i < 2; i++) {
		objects[i].mv = view * objects[i].model;

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
	
	objects[0] = Object();
	objects[1] = Object();

}

//------------------------------------------------------------
// void Render(int n)
// Render method that is called by the timer function
//------------------------------------------------------------

void Render(int n) {
	Render();
	glutTimerFunc(DELTA_TIME, Render, 0);
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
	bool res = loadOBJ("Objects/car.obj", objects[0].vertices, objects[0].uvs, objects[0].normals);

	bool res1 = loadOBJ("Objects/torus.obj", objects[1].vertices, objects[1].uvs, objects[1].normals);

	objects[0].texture_id = loadBMP("Textures/Yellobrk.bmp");
	objects[1].texture_id = loadBMP("Textures/uvtemplate.bmp");
}

//------------------------------------------------------------
// void InitMatrices()
// 
//------------------------------------------------------------

void InitMatrices(int i) {
	objects[i].model = glm::mat4();
	view = glm::lookAt(
		glm::vec3(2.0, 2.0, 4.0),  // eye
		glm::vec3(0.0, 0.5, 0.0),  // center
		glm::vec3(0.0, 1.0, 0.0));  // up

	projection = glm::perspective(
		glm::radians(45.0f),
		1.0f * WIDTH / HEIGHT, 0.1f,
		20.0f);

	objects[i].mv = view * objects[i].model;
}

void InitLight() {
	light.position = glm::vec3(4.0, 4.0, 4.0);

	objects[0].material.ambient_color = glm::vec3(0.2, 0.2, 0.1);
	objects[0].material.diffuse_color = glm::vec3(0.5, 0.5, 0.3);
	objects[0].material.specular = glm::vec3(0.7, 0.7,0.7);
	objects[0].material.power = 1024.0f;

	objects[1].material.ambient_color = glm::vec3(0.2, 0.2, 0.1);
	objects[1].material.diffuse_color = glm::vec3(1.0, 1.0, 1.0);
	objects[1].material.specular = glm::vec3(0.7, 0.7, 0.7);
	objects[1].material.power = 1024.0f;
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

		objects[i].mv = view * objects[i].model;

		// Send mvp
		glUseProgram(program_id);
		glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, glm::value_ptr(objects[i].mv));
		glUniformMatrix4fv(uniform_proj, 1, GL_FALSE, glm::value_ptr(projection));

	}


}


int main(int argc, char** argv) {
	
	InitGlutGlew(argc, argv);
	InitShaders();
	InitMatrices(0);
	InitMatrices(1);
	InitObjects();
	InitLight();
	InitBuffers();


	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	// Main loop
	glutMainLoop();

	return 0;
}
