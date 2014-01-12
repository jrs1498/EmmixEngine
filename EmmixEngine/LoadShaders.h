#pragma once
#include <iostream>

#include <GL\glew.h>



/*
glShaderInfo pairs a opengl shader type with a specified shader file
*/
struct glShaderInfo
{
	GLenum			glShaderType;
	const char		* glShaderFilename;
};



/*
LoadShaders class provides a simple interface to load a collection of shaders
*/
class LoadShaders
{
public:
	static GLuint loadShaders( glShaderInfo * shaderInfo, const char * shaderDirectory );

private:
	static const GLchar * readShader( char * shaderSource );
	static GLenum shaderStatus( GLuint & shader, GLenum parameter );
	static GLenum programStatus( GLuint & program, GLenum parameter );
};

