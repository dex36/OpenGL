#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>

#include <vector>
#include <GL\glew.h> // UP
#include <GL\glut.h>
#include <GLFW\glfw3.h>
#include <SDL.h>

#define GLM_FORCE_RADIANS
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "vertex_loader.h"
//#include "obj_loader.h"

using namespace glm;
using namespace std;

GLuint LoadTexture(const char * filename)
{
		int width = 0, height = 0, n = 0;
		unsigned char* data = stbi_load(filename,&width,&height,&n,3);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glActiveTexture(GL_TEXTURE0);
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
 
        return texture;
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

	GLuint program = Program::Load
		(
		vert, GL_VERTEX_SHADER,
		frag, GL_FRAGMENT_SHADER,
		NULL
		);
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

	///VBO
	GLuint vboID;
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//VBO ARRAY
	GLuint indexbuff;
	glGenBuffers(1, &indexbuff);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuff);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//VAO
	GLuint vertexarray;
	glGenVertexArrays(1, &vertexarray);
	glBindVertexArray(vertexarray);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)(sizeof(float) * 3));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)(sizeof(float) * 6));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (char*)(sizeof(float) * 8));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuff);
	glBindVertexArray(0);


	Camera camera;
	static float xlight = 2.0f;
	static float ylight = 2.0f;
	static float time = 0.0f;

	///////////////////////

	#define HM_SIZE_X 4 
	#define HM_SIZE_Y 4

	float fHeights[HM_SIZE_X*HM_SIZE_Y] =
	{
		4.0f, 2.0f, 3.0f, 1.0f,
		3.0f, 5.0f, 8.0f, 2.0f,
		7.0f, 10.0f, 12.0f, 6.0f,
		4.0f, 6.0f, 8.0f, 3.0f
	};
	float fSizeX = 40.0f, fSizeZ = 40.0f;

	glm::vec3 vHeightmapData[HM_SIZE_X*HM_SIZE_Y];
	for (int i = 0; i<HM_SIZE_X*HM_SIZE_Y; i++)
	{
		float column = float(i%HM_SIZE_X);
		float row = float(i / HM_SIZE_X);
		vHeightmapData[i] = glm::vec3(-fSizeX / 2 + fSizeX*column / float(HM_SIZE_X - 1), fHeights[i],-fSizeZ / 2 + fSizeZ*row / float(HM_SIZE_Y - 1));
	}
	int iIndices[] =
	{
		0, 4, 1, 5, 2, 6, 3, 7, 16, // First row, then restart
		4, 8, 5, 9, 6, 10, 7, 11, 16, // Second row, then restart
		8, 12, 9, 13, 10, 14, 11, 15, // Third row, no restart
	};

	GLuint uiVBOHeightmapData; 
	glGenBuffers(1, &uiVBOHeightmapData); 
	glBindBuffer(GL_ARRAY_BUFFER, uiVBOHeightmapData);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*HM_SIZE_X*HM_SIZE_Y, vHeightmapData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint uiVBOIndices; 
	glGenBuffers(1, &uiVBOIndices); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiVBOIndices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(iIndices), iIndices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	GLuint uiVAOHeightmap; 
	glGenVertexArrays(1, &uiVAOHeightmap); 
	glBindVertexArray(uiVAOHeightmap);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uiVBOHeightmapData);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiVBOIndices);
	glBindVertexArray(0);
	///////////////////////////////

	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);



	while (!glfwWindowShouldClose(window))
	{
		
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glEnable(GL_CULL_FACE);
		///
		const GLfloat color[] = { (float)sin(time) * 0.5f + 0.5f,(float)cos(time) * 0.5f + 0.5f,0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, color);
		time += 0.001f;
		////

		glUseProgram(program);
		
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
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		if (xpos > 0 && xpos < 640 && ypos>0 && ypos < 400){
			camera.mouseUpdate(vec2(float(xpos / 50), float(ypos / 50)));
		}

		// Textures
		glUniform1i(glGetUniformLocation(program, "mySampler"), 0);

		//Ambient Light
		GLint ambientlightlocation = glGetUniformLocation(program, "ambientLight");
		vec3 ambientLight(0.3f, 0.3f, 0.3f);
		glUniform3fv(ambientlightlocation, 1, &ambientLight[0]);

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
			xlight += 0.01f;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
			xlight -= 0.01f;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
			ylight += 0.01f;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
			ylight -= 0.01f;
		}
		//Light
		GLint lightlocation = glGetUniformLocation(program, "lightPosition");
		vec3 lightposition(xlight, ylight, -4.0f);
		glUniform3fv(lightlocation, 1, &lightposition[0]);

		//World
		GLint fullTransformMatrixUniformLocation = glGetUniformLocation(program, "fullTransformMatrix");
		mat4 fullTransformMatrix;
		mat4 projectionMatrix = perspective(90.0f, (480.0f / 640.0f), 0.1f, 20.0f);
		mat4 worldToProjectionMatrix = projectionMatrix* camera.getWorldToViewMatrix();


		//CUBE 1
		glBindVertexArray(vertexarray);
		glBindTexture(GL_TEXTURE_2D, LoadTexture("block.jpg"));

		mat4 cube1WorldMatrix = translate(vec3(1.0f, 0.0f, -3.75f)) * rotate(0.0f, vec3(0.0f, 1.0f, 1.0f));
		fullTransformMatrix = worldToProjectionMatrix *cube1WorldMatrix;
		glUniformMatrix4fv(fullTransformMatrixUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);

		mat4 cube2WorldMatrix = translate(vec3(-3.0f, 0.0f, -3.75f)) * rotate(126.0f, vec3(1.0f, 0.0f, 0.0f));
		fullTransformMatrix = worldToProjectionMatrix *cube2WorldMatrix;
		glUniformMatrix4fv(fullTransformMatrixUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
	
		//Terrain
		glBindVertexArray(uiVAOHeightmap);
		glBindTexture(GL_TEXTURE_2D, LoadTexture("block.jpg"));

		glEnable(GL_PRIMITIVE_RESTART);
		glPrimitiveRestartIndex(HM_SIZE_X*HM_SIZE_Y);

		mat4 cube2WorldMatrix2 = translate(vec3(0.0f, -15.0f, 0.0f)) * rotate(0.0f, vec3(1.0f, 0.0f, 0.0f));
		fullTransformMatrix = worldToProjectionMatrix *cube2WorldMatrix2;
		glUniformMatrix4fv(fullTransformMatrixUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
		glDrawElements(GL_TRIANGLE_STRIP, HM_SIZE_X*(HM_SIZE_Y - 1) * 2 + HM_SIZE_Y - 2, GL_UNSIGNED_INT, 0);

		glDisable(GL_PRIMITIVE_RESTART);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

