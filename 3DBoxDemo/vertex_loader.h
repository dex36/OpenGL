#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <GL\glew.h> // UP
#include <GL\glut.h>
#include <GLFW\glfw3.h>
#include <SDL.h>

#define GLM_FORCE_RADIANS
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>

using namespace glm;

struct Program
{
	static GLuint Load(const char* shader, ...)
	{
		GLuint prog = glCreateProgram();
		va_list args;
		va_start(args, shader);
		while (shader)
		{
			const GLenum type = va_arg(args, GLenum);
			AttachShader(prog, type, shader);
			shader = va_arg(args, const char*);
		}
		va_end(args);
		glLinkProgram(prog);
		CheckStatus(prog);
		return prog;
	}

private:
	static void CheckStatus(GLuint obj)
	{
		GLint status = GL_FALSE;
		if (glIsShader(obj)) glGetShaderiv(obj, GL_COMPILE_STATUS, &status);
		if (glIsProgram(obj)) glGetProgramiv(obj, GL_LINK_STATUS, &status);
		if (status == GL_TRUE) return;
		GLchar log[1 << 15] = { 0 };
		if (glIsShader(obj)) glGetShaderInfoLog(obj, sizeof(log), NULL, log);
		if (glIsProgram(obj)) glGetProgramInfoLog(obj, sizeof(log), NULL, log);
		std::cerr << log << std::endl;
		exit(EXIT_FAILURE);
	}

	static void AttachShader(GLuint program, GLenum type, const char* src)
	{
		GLuint shader = glCreateShader(type);
		glShaderSource(shader, 1, &src, NULL);
		glCompileShader(shader);
		CheckStatus(shader);
		glAttachShader(program, shader);
		glDeleteShader(shader);
	}
};

#define GLSL(version, shader) "#version " #version "\n" #shader

const char* vert = GLSL
(
330 core,
layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 vertexUV;
layout(location = 3) in vec3 normal;

uniform mat4 fullTransformMatrix;

uniform vec3 ambientLight;
uniform vec3 lightPosition;

out vec3 theColor;
out vec2 UV;

void main()
{
	vec4 v = vec4(in_pos, 1.0);
	gl_Position = fullTransformMatrix* v;

	vec3 lightVector = normalize(lightPosition - normal);
	float brightness = dot(lightVector, normal);
	theColor = vertexColor * vec3(brightness, brightness, brightness);// * ambientLight;

	UV = vertexUV;
}
);

const char* frag = GLSL
(
330 core,
out vec4 color;

in vec3 theColor;
in vec2 UV;

uniform sampler2D mySampler;

void main()
{
	color = texture(mySampler, UV);
}
);
