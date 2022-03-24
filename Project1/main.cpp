#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glsl.h"
#include "objloader.h"
#include "texture.h"

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

struct Material {
	glm::vec3 ambient_color;
	glm::vec3 diffuse_color;
	glm::vec3 specular;
	float power = 1024;
};

//--------------------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------------------

// ID's
GLuint program_id;
GLuint texture_id[2];
GLuint vao[2];

// Uniform ID's
GLuint uniform_mv;
GLuint uniform_material_ambient;
GLuint uniform_material_diffuse;
GLuint uniform_material_specular;
GLuint uniform_material_power;
GLuint uniform_light_pos;
//GLuint uniform_light_pos;

// Matrices
glm::mat4 model[2], view, projection;
glm::mat4 mv[2];

LightSource light;
Material material[2];

vector <glm::vec3> normals[2];
vector <glm::vec3> vertices[2];
vector <glm::vec2> uvs[2];

//--------------------------------------------------------------------------------
// Mesh variables
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
// Keyboard handling
//--------------------------------------------------------------------------------

void keyboardHandler(unsigned char key, int a, int b) {
	if (key == 27)
		glutExit();
}


//--------------------------------------------------------------------------------
// Rendering
//--------------------------------------------------------------------------------

void Render() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Do transformation
	model[0] = glm::rotate(model[0], 0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
	model[1] = glm::rotate(model[1], 0.01f, glm::vec3(0.0f, 1.0f, 0.0f));

	// Attach to program_id
	glUseProgram(program_id);


	for (int i = 0; i < 2; i++) {
		mv[i] = view * model[i];

		// Send mvp
		glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, glm::value_ptr(mv[i]));

		glBindTexture(GL_TEXTURE_2D, texture_id[i]);

	

		// Send vao
		glBindVertexArray(vao[i]);
		glDrawArrays(GL_TRIANGLES, 0, vertices[i].size());
		glBindVertexArray(0);

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
	bool res = loadOBJ("Objects/car.obj", vertices[0], uvs[0], normals[0]);
	bool res1 = loadOBJ("Objects/torus.obj", vertices[1], uvs[1], normals[1]);

	texture_id[0] = loadBMP("Textures/Yellobrk.bmp");
	texture_id[1] = loadBMP("Textures/uvtemplate.bmp");
}

//------------------------------------------------------------
// void InitMatrices()
//------------------------------------------------------------

void InitMatrices(int i) {
	model[i] = glm::mat4();
	view = glm::lookAt(
		glm::vec3(2.0, 2.0, 4.0),  // eye
		glm::vec3(0.0, 0.5, 0.0),  // center
		glm::vec3(0.0, 1.0, 0.0));  // up

	projection = glm::perspective(
		glm::radians(45.0f),
		1.0f * WIDTH / HEIGHT, 0.1f,
		20.0f);

	mv[i] = view * model[i];
}

void InitLight() {
	light.position = glm::vec3(4.0, 4.0, 4.0);

	material[0].ambient_color = glm::vec3(0.2, 0.2, 0.1);
	material[0].diffuse_color = glm::vec3(0.5, 0.5, 0.3);
	material[0].specular = glm::vec3(0.7, 0.7,0.7);
	material[0].power = 1024.0f;

	material[1].ambient_color = glm::vec3(0.2, 0.2, 0.1);
	material[1].diffuse_color = glm::vec3(1.0, 1.0, 1.0);
	material[1].specular = glm::vec3(0.7, 0.7, 0.7);
	material[1].power = 1024.0f;
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

	for (int i = 0; i < 2; i++) {
		glGenBuffers(1, &vbo_normals);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
		glBufferData(GL_ARRAY_BUFFER,
			normals[i].size() * sizeof(glm::vec3),
			&normals[i][0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &vbo_vertices);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
		glBufferData(GL_ARRAY_BUFFER,
			vertices[i].size() * sizeof(glm::vec3), &vertices[i][0],
			GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &vbo_uvs);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_uvs);
		glBufferData(GL_ARRAY_BUFFER, uvs[i].size() * sizeof(glm::vec2),
			&uvs[i][0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Allocate memory for vao
		glGenVertexArrays(1, &vao[i]);

		// Bind to vao
		glBindVertexArray(vao[i]);

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
		glUniform3fv(uniform_material_ambient, 1, glm::value_ptr(material[i].ambient_color));
		glUniform3fv(uniform_material_diffuse, 1, glm::value_ptr(material[i].diffuse_color));
		glUniform1f(uniform_material_power, material[i].power);
		glUniform3fv(uniform_material_specular, 1, glm::value_ptr(material[i].specular));
		// Define model
		mv[i] = view * model[i];



		// Send mvp
		glUseProgram(program_id);
		glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, glm::value_ptr(mv[i]));
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
