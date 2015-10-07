#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <GL\glew.h> // UP
#include <GL\glut.h>
#include <GLFW\glfw3.h>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include <SDL.h>

using namespace glm;

GLuint LoadTexture(const char * filename)
{
	int width, height;
	GLubyte * data;
	FILE * file;
	file = fopen(filename, "rb");
	if (file == NULL) return 0;
	width = 128;
	height = 128;
	data = (GLubyte *)malloc(width * height * 3);
	//int size = fseek(file,);
	fread(data, width * height * 3, 1, file);
	fclose(file);
	for (int i = 0; i < width * height; ++i)
	{
		int index = i * 3;
		unsigned char B, R;
		B = data[index];
		R = data[index + 2];

		data[index] = R;
		data[index + 2] = B;
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glActiveTexture(GL_TEXTURE0);
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	//free(data);

	return texture;
	/**
	SDL_Surface* textures;
	textures = SDL_LoadBMP(filename);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, textures->w, textures->h, 0, GL_RGB, GL_UNSIGNED_BYTE, textures->pixels);
	return texture;
	**/
}
std::string LoadFileToString(const char* filepath){
	std::string fileData = "";
	std::ifstream stream(filepath, std::ios::in);

	if (stream.is_open()){
		std::string line = "";
		while (getline(stream, line)){
			fileData += "\n" + line;
		}
		stream.close();
	}
	return fileData;
}
GLuint LoadShaders(const char*VertShaderPath, const char* fragShaderPath){
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertShaderSource = LoadFileToString(VertShaderPath);
	std::string fragShaderSource = LoadFileToString(fragShaderPath);

	const char*  rawVertShaderSource = vertShaderSource.c_str();
	const char*  rawfragShaderSource = fragShaderSource.c_str();

	glShaderSource(vertShader, 1, &rawVertShaderSource, NULL);
	glShaderSource(fragShader, 1, &rawfragShaderSource, NULL);

	glCompileShader(vertShader);
	glCompileShader(fragShader);

	GLuint program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	return program;
}

const float movementspeed = 0.01f;
class Camera{
	vec3 position;
	vec3 viewDirection;
	const vec3 UP;
	vec2 oldmouseposition;
public:
	Camera();
	mat4 getWorldToViewMatrix() const;
	void mouseUpdate(const vec2 &newMousePosition);
	void moveForward();
	void moveBackWard();
	void left();
	void right();
	void up();
	void down();

};
Camera::Camera() :viewDirection(0.0f, 0.0f, -1.0f), UP(0.0f, 1.0f, 0.0f){}
void Camera::mouseUpdate(const vec2 &newMousePosition){

	glm::vec2 mouseDelta = newMousePosition - oldmouseposition;
	if (glm::length(mouseDelta) >10.0f)
	{
		oldmouseposition = newMousePosition;
		return;
	}
	viewDirection = glm::mat3(glm::rotate(-mouseDelta.x*0.5f, UP)) * viewDirection;
	oldmouseposition = newMousePosition;

}
void Camera::moveForward(){
	position -= movementspeed *viewDirection;
}
void Camera::moveBackWard(){
	position += movementspeed *viewDirection;
}
void Camera::left(){
	glm::vec3 strafeDirection = glm::cross(viewDirection, UP);
	position += movementspeed *strafeDirection;
}
void Camera::right(){
	glm::vec3 strafeDirection = glm::cross(viewDirection, UP);
	position += -movementspeed *strafeDirection;
}
void Camera::up(){
	position += movementspeed *UP;
}
void Camera::down(){
	position += -movementspeed *UP;
}
mat4 Camera::getWorldToViewMatrix() const {
	return lookAt(position, position - viewDirection, UP);
}


int main(int argc, char ** argv)
{
	if (!glfwInit())
		exit(EXIT_FAILURE);

	GLFWwindow* window;
	window = glfwCreateWindow(640, 480, "My 3D World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glewExperimental = true;
	if (glewInit() != GLEW_OK){
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	GLuint program = LoadShaders("vertex.wss", "fragment.fss"); // shadersprogram
	
	struct Vertex{
		glm::vec3 position;
		glm::vec3 color;
		glm::vec2 texture;
		glm::vec3 normal;
	};
	Vertex verts[] = {
		vec3(-1.0f, +1.0f, +1.0f), // 0
		vec3(0.0f, 1.0f, 0.0f), // Colour
		vec2(0.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f), //normal
		vec3(+1.0f, +1.0f, +1.0f), // 1
		vec3(0.0f, 0.0f, 1.0f), // Colour
		vec2(1.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f), //normal
		vec3(+1.0f, +1.0f, -1.0f), // 2
		vec3(1.0f, 0.0f, 0.0f), // Colour
		vec2(1.0f, 1.0f),
		vec3(0.0f, 1.0f, 0.0f), //normal
		vec3(-1.0f, +1.0f, -1.0f), // 3
		vec3(0.0f, 0.0f, 0.0f), // Colour
		vec2(0.0f, 1.0f),
		vec3(0.0f, 1.0f, 0.0f), //normal

		vec3(-1.0f, +1.0f, -1.0f), // 4
		vec3(0.0f, 1.0f, 0.0f), // Colour
		vec2(0.0f, 0.0f),
		vec3(0.0f, -1.0f, 0.0f), //normal
		vec3(+1.0f, +1.0f, -1.0f), // 5
		vec3(1.0f, 0.0f, 0.0f), // Colour
		vec2(1.0f, 0.0f),
		vec3(0.0f, -1.0f, 0.0f), //normal
		vec3(+1.0f, -1.0f, -1.0f), // 
		vec3(0.0f, 0.0f, 1.0f), // Colour
		vec2(1.0f, 1.0f),
		vec3(0.0f, -1.0f, 0.0f), //normal
		vec3(-1.0f, -1.0f, -1.0f), // 7
		vec3(0.0f, 1.0f, 0.0f), // Colour
		vec2(0.0f, 1.0f),
		vec3(0.0f, -1.0f, 0.0f), //normal

		vec3(+1.0f, +1.0f, -1.0f), // 8
		vec3(0.0f, 0.0f, 1.0f), // Colour
		vec2(0.0f, 0.0f),
		vec3(0.0f, 0.0f, -1.0f), //normal
		vec3(+1.0f, +1.0f, +1.0f), // 9
		vec3(0.0f, 1.0f, 0.0f), // Colour
		vec2(1.0f, 0.0f),
		vec3(0.0f, 0.0f, -1.0f), //normal
		vec3(+1.0f, -1.0f, +1.0f), // 10
		vec3(0.0f, 0.0f, 1.0f), // Colour
		vec2(1.0f, 1.0f),
		vec3(0.0f, 0.0f, -1.0f), //normal
		vec3(+1.0f, -1.0f, -1.0f), // 11
		vec3(0.0f, 0.0f, 1.0f), // Colour
		vec2(0.0f, 1.0f),
		vec3(0.0f, 0.0f, -1.0f), //normal

		vec3(-1.0f, +1.0f, +1.0f), // 12
		vec3(0.0f, 0.0f, 1.0f), // Colour
		vec2(0.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f), //normal
		vec3(-1.0f, +1.0f, -1.0f), // 13
		vec3(1.0f, 0.0f, 0.0f), // Colour
		vec2(1.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f), //normal
		vec3(-1.0f, -1.0f, -1.0f), // 14
		vec3(0.0f, 1.0f, 0.0f), // Colour
		vec2(1.0f, 1.0f),
		vec3(0.0f, 1.0f, 0.0f), //normal
		vec3(-1.0f, -1.0f, +1.0f), // 15
		vec3(0.0f, 1.0f, 0.0f), // Colour
		vec2(0.0f, 1.0f),
		vec3(0.0f, 1.0f, 0.0f), //normal

		vec3(+1.0f, +1.0f, +1.0f), // 16
		vec3(0.0f, 0.0f, 1.0f), // Colour
		vec2(0.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f), //normal
		vec3(-1.0f, +1.0f, +1.0f), // 17
		vec3(1.0f, 0.0f, 1.0f), // Colour
		vec2(1.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f), //normal
		vec3(-1.0f, -1.0f, +1.0f), // 18
		vec3(0.0f, 1.0f, 0.0f), // Colour
		vec2(1.0f, 1.0f),
		vec3(0.0f, 1.0f, 0.0f), //normal
		vec3(+1.0f, -1.0f, +1.0f), // 19
		vec3(1.0f, 0.0f, 1.0f), // Colour
		vec2(0.0f, 1.0f),
		vec3(0.0f, 1.0f, 0.0f), //normal

		vec3(+1.0f, -1.0f, -1.0f), // 20
		vec3(0.0f, 1.0f, 0.0f), // Colour
		vec2(0.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f), //normal
		vec3(-1.0f, -1.0f, -1.0f), // 21
		vec3(0.0f, 1.0f, 0.0f), // Colour
		vec2(1.0f, 0.0f),
		vec3(0.0f, 1.0f, 0.0f), //normal
		vec3(-1.0f, -1.0f, +1.0f), // 22
		vec3(0.0f, 1.0f, 1.0f), // Colour
		vec2(1.0f, 1.0f),
		vec3(0.0f, 1.0f, 0.0f), //normal
		vec3(+1.0f, -1.0f, +1.0f), // 23
		vec3(1.0f, 1.0f, 0.0f), // Colour
		vec2(0.0f, 1.0f),
		vec3(0.0f, 1.0f, 0.0f) //normal
	};
	GLushort indices[] = {
		0, 1, 2, 0, 2, 3, // Top
		4, 5, 6, 4, 6, 7, // Front
		8, 9, 10, 8, 10, 11, // Right
		12, 13, 14, 12, 14, 15, // Left
		16, 17, 18, 16, 18, 19, // Back
		20, 22, 21, 20, 23, 22 // Bottom
	};
	////////VAO niepotrzebne
	////////VBO
	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	GLuint indexbuff;
	glGenBuffers(1, &indexbuff);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuff);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
	//////


	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, LoadTexture("block"));

	Camera camera;

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		
		

		glUseProgram(program);

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
			camera.moveForward();
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
			camera.moveBackWard();
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
			camera.left();
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
			camera.right();
		}
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
			camera.up();
		}
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS){
			camera.down();
		}
		if (xpos > 0 && xpos < 640 && ypos>0 && ypos < 400){
			camera.mouseUpdate(vec2(float(xpos / 50), float(ypos / 50)));
			std::cout << "pos x: " << xpos << "pos y: " << ypos << std::endl;
		}

		// textures
		glUniform1i(glGetUniformLocation(program, "mySampler"), 0);
		//AMBIENT LIGHT
		GLint ambientlightlocation = glGetUniformLocation(program, "ambientLight");
		vec3 ambientLight(0.3f, 0.3f, 0.3f);
		glUniform3fv(ambientlightlocation, 1, &ambientLight[0]);

		//Light
		GLint lightlocation = glGetUniformLocation(program, "lightPosition");
		vec3 lightposition(1.0f, 1.0f, -3.75f);
		glUniform3fv(lightlocation, 1, &lightposition[0]);


		GLint fullTransformMatrixUniformLocation = glGetUniformLocation(program, "fullTransformMatrix");
		mat4 fullTransformMatrix;
		mat4 projectionMatrix = perspective(90.0f, (480.0f / 640.0f), 0.1f, 5.0f);
		mat4 worldToProjectionMatrix = projectionMatrix* camera.getWorldToViewMatrix();

		//CUBE 1 tak sie robi gdyby sie roznily
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (char*)(sizeof(float) * 3));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (char*)(sizeof(float) * 6));
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (char*)(sizeof(float) * 9));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuff);

		mat4 cube1WorldMatrix = translate(vec3(1.0f, 0.0f, -3.75f)) * rotate(0.0f, vec3(0.0f, 1.0f, 1.0f));
		fullTransformMatrix = worldToProjectionMatrix *cube1WorldMatrix;
		glUniformMatrix4fv(fullTransformMatrixUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
		
		// CUBE 2 gdyby byly rozne 
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (char*)(sizeof(float) * 3));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (char*)(sizeof(float) * 6));
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (char*)(sizeof(float) * 9));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuff);

		mat4 cube2WorldMatrix = translate(vec3(-3.0f, 0.0f, -3.75f)) * rotate(126.0f, vec3(1.0f, 0.0f, 0.0f));
		fullTransformMatrix = worldToProjectionMatrix *cube2WorldMatrix;
		glUniformMatrix4fv(fullTransformMatrixUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);


		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
