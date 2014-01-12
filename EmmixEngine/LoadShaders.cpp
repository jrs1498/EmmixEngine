#include "LoadShaders.h"


/*
Attempts to load a collection of shader files defined in the shaderInfo parameter. Searches for the files
in the directory specified by shaderDirectory.

If successful, returns the newly created and bound programID. Produces and error otherwise
*/
GLuint LoadShaders::loadShaders( glShaderInfo * shaderInfo, const char * shaderDirectory )
{
	// Create the program
	GLuint programID = glCreateProgram();

	// Count the number of shaders passed in
	int numShaders = 0;
	while( shaderInfo[numShaders].glShaderType != NULL )
		numShaders++;

	// Generate each shader
	for( int i = 0; i < numShaders; i++ )
	{
		// Local variable for the current glShaderInfo
		glShaderInfo * currShaderInfo = &shaderInfo[i];

		// Create the shader
		GLuint shader = glCreateShader( currShaderInfo->glShaderType );

		// Get the source code's full path
		char sourceCodePath[512];
		strcpy( sourceCodePath, shaderDirectory );
		strcat( sourceCodePath, currShaderInfo->glShaderFilename );

		// Read the source code, terminate function if failed
		const GLchar * sourceCode = readShader( sourceCodePath );
		if( sourceCode == NULL )
			return -1;

		// Set the source code and compile the shader
		glShaderSource( shader, 1, &sourceCode, NULL );
		glCompileShader( shader );

		// Verify the shader compiled successfully
		if( shaderStatus( shader, GL_COMPILE_STATUS ) != GL_TRUE )
		{
			glDeleteShader( shader );
			return -1;
		}

		// Attach the shader
		glAttachShader( programID, shader );
	}

	// Link the program after all shaders have been parsed
	glLinkProgram( programID );

	// Verify successful linking
	if( programStatus( programID, GL_LINK_STATUS ) != GL_TRUE )
	{
		glDeleteProgram( programID );
		return -1;
	}

	// At this point, all is successful. Return the programID
	return programID;
}




/*
Parses a specified shader source code file and returns the source code as a collection of GLchar
*/
const GLchar * LoadShaders::readShader( char * shaderSource )
{
	// Open the file
	FILE * shaderFile;

#ifdef WIN32
	// fopen_s is the preffered open function on WIN32
	fopen_s( &shaderFile, shaderSource, "rb" );
#else
	// Otherwise, use fopen
	shaderFile = fopen( shaderSource, "rb" );
#endif

	// Verify the file opened successfully
	if( !shaderFile )
	{
		std::cerr << "Failed to load shader: " << shaderSource << std::endl;
		return NULL;
	}

	// Get the length of the file in number of chars
	fseek( shaderFile, 0, SEEK_END );
	int fileLength = ftell( shaderFile );
	fseek( shaderFile, 0, SEEK_SET );

	// GLchar string to hold the source code
	GLchar * sourceCode = new GLchar[fileLength + 1];

	// Read in the source code
	fread( sourceCode, sizeof(GLchar), fileLength, shaderFile );
	fclose( shaderFile );

	sourceCode[fileLength] = 0;

	return const_cast<const GLchar *>( sourceCode );
}




/*
Checks the shader's status using glGetShaderiv. If an error is encountered, it is reported.
*/
GLenum LoadShaders::shaderStatus( GLuint & shader, GLenum parameter )
{
	// Check the status
	GLint status;
	glGetShaderiv( shader, parameter, &status );

	// If this is a compile status check and it failed, print the log
	if( parameter == GL_COMPILE_STATUS && status != GL_TRUE )
	{
		GLint logLengthMax;
		GLint length;
		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logLengthMax );
		char * log = new char[logLengthMax];
		glGetShaderInfoLog( shader, logLengthMax, &length, log );
		std::cerr << log << std::endl;
	}

	// Return the status
	return status;
}




/*
Checks the program's status using glGetProgramiv. If an error is encountered, it is reported.
*/
GLenum LoadShaders::programStatus( GLuint & program, GLenum parameter )
{
	GLint status;
	glGetProgramiv( program, parameter, &status );

	// If this is a link status check and it failed, print the log
	if( parameter == GL_LINK_STATUS && status != GL_TRUE )
	{
		GLint logLengthMax;
		GLint length;
		glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logLengthMax );
		char * log = new char[logLengthMax];
		glGetProgramInfoLog( program, logLengthMax, &length, log );
		std::cerr << log << std::endl;
	}

	// Return the status
	return status;
}