#include "Scene.h"


Scene::Scene( GLFWwindow * pWindow )
	:	_pWindow		( pWindow ),
		_camera			( 45.0f, 4.0f / 3.0f, 0.1f, 100.0f )
{
}


Scene::~Scene(void)
{
}




/*
Performs all necessary scene initialization functions
*/
bool Scene::initScene( void )
{
	// Generate VAOs
	glGenVertexArrays( _NumVAOIDs, VAOs );

	// Generate Buffers
	glGenBuffers( _NumBuffIDs, Buffers );

	// Load shaders
	if( !loadShaders() )
		return false;

	// Load some example meshes
	std::vector<glm::vec3> mesh1verts;
	std::vector<glm::vec3> mesh2verts;

	mesh1verts.push_back( glm::vec3( 0.0f, 0.0f, 0.0f ) );	// Tri 1
	mesh1verts.push_back( glm::vec3( 1.0f, 0.0f, 0.0f ) );
	mesh1verts.push_back( glm::vec3( 0.0f, 0.0f, 1.0f ) );

	mesh1verts.push_back( glm::vec3( 1.0f, 0.0f, 0.0f ) );	// Tri 2
	mesh1verts.push_back( glm::vec3( 0.0f, 0.0f, 1.0f ) );
	mesh1verts.push_back( glm::vec3( 1.0f, 0.0f, 1.0f ) );

	mesh1verts.push_back( glm::vec3( 0.0f, 0.0f, 0.0f ) );	// Tri 3
	mesh1verts.push_back( glm::vec3( 1.0f, 0.0f, 0.0f ) );
	mesh1verts.push_back( glm::vec3( 0.0f, 1.0f, 0.0f ) );

	mesh1verts.push_back( glm::vec3( 1.0f, 0.0f, 0.0f ) );	// Tri 4
	mesh1verts.push_back( glm::vec3( 0.0f, 1.0f, 0.0f ) );
	mesh1verts.push_back( glm::vec3( 1.0f, 1.0f, 0.0f ) );



	mesh2verts.push_back( glm::vec3( -0.9f, -0.9f, 0.0 ) );
	mesh2verts.push_back( glm::vec3( -0.9f, 0.9f, 0.0 ) );
	mesh2verts.push_back( glm::vec3( 0.9f, -0.9f, 0.0 ) );

	Mesh mesh1( mesh1verts );
	Mesh mesh2( mesh2verts );

	mesh1.move( glm::vec3( 0.0f, 1.0f, 0.0f ) );

	_meshes.push_back( mesh1 );
	_meshes.push_back( mesh2 );

	_camera.move( glm::vec3( 0.0f, 0.0f, -10.0f ) );

	return true;
}




/*
Loads the shaders that will be used to render this scene
*/
bool Scene::loadShaders( void )
{
	// Shader directory
	const char * shaderDirectory = "";

	// Specify shaders we will be loading
	glShaderInfo shaderInfo[] = 
	{
		GL_VERTEX_SHADER,		"vertexshader.vsh",
		GL_FRAGMENT_SHADER,		"fragmentshader.frag",
		NULL,					""
	};

	// Load the shaders
	_ID_program = LoadShaders::loadShaders( shaderInfo, shaderDirectory );

	// Verify success
	if( _ID_program == -1 )
		return false;


	// Get shader uniform IDs
	_ID_matr_model			= glGetUniformLocation		( _ID_program, "matr_model" );
	_ID_matr_view			= glGetUniformLocation		( _ID_program, "matr_view" );
	_ID_matr_projection		= glGetUniformLocation		( _ID_program, "matr_projection" );
	_ID_matr_mvp			= glGetUniformLocation		( _ID_program, "matr_mvp" );



	// If we have made it here, shaders loaded successfully
	return true;
}





// --------------------------------------------------------------------------------------------------------------------------------------




/*
This function is called once per cycle
*/
void Scene::processFrame( void )
{
	// Start clock
	_sceneClock.startClock();

	updateScene();
	renderScene();

	// Stop clock
	_sceneClock.stopClock();
}




/*
Process one iteration of the scene's simulation
*/
void Scene::updateScene( void )
{
}




/*
Render the current frame to the screen
*/
void Scene::renderScene( void )
{
	// Clear screen
	glClear( GL_COLOR_BUFFER_BIT );

	// Use the shader program
	glUseProgram( _ID_program );

	// Bind our VAO
	glBindVertexArray( VAOs[_VAOID_Triangle] );


	// Grab projection and view matrices from the camera
	const glm::mat4 matr_view = _camera.getViewMatrix();
	glUniformMatrix4fv( _ID_matr_view, 1, GL_FALSE, &matr_view[0][0] );

	const glm::mat4 matr_projection = _camera.getProjectionMatrixPerspective();
	glUniformMatrix4fv( _ID_matr_projection, 1, GL_FALSE, &matr_projection[0][0] );


	// For each mesh
	for( unsigned int i = 0; i < _meshes.size(); i++ )
	{
		// Local variable for the current mesh
		Mesh * currentMesh = &_meshes[i];
		std::vector<glm::vec3> vertices = *currentMesh->getVertices();


		// Grab model and mvp matrices and pass them off to the shaders
		const glm::mat4 matr_model = currentMesh->getModelMatrix();
		glUniformMatrix4fv( _ID_matr_model, 1, GL_FALSE, &matr_model[0][0] );

		const glm::mat4 matr_mvp = matr_projection * matr_view * matr_model;
		glUniformMatrix4fv( _ID_matr_mvp, 1, GL_FALSE, &matr_mvp[0][0] );


		// Vertex Attribute 0 : Position
		glEnableVertexAttribArray( 0 );
		glBindBuffer( GL_ARRAY_BUFFER, Buffers[_BuffID_Vertex] );
		glBufferData(
			GL_ARRAY_BUFFER,
			vertices.size() * sizeof( glm::vec3 ),
			&vertices[0],
			GL_STATIC_DRAW
			);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
			);

		
		// Draw arrays
		glDrawArrays( GL_TRIANGLES, 0, vertices.size() );

		
		// Disable vertex attribute pointers
		glDisableVertexAttribArray( 0 );
	}



	// Swap buffers to show the new frame
	glfwSwapBuffers( _pWindow );
}