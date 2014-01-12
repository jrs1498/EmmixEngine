#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Scene\Scene.h"



// Window
GLFWwindow		* _window;
const int		INITIAL_WINDOW_WIDTH		= 1024;
const int		INITIAL_WINDOW_HEIGHT		= 768;


// Scene
Scene			* _scene;






/*
Deallocate the heap. Should be called before exiting
*/
void deallocate( void )
{
	delete _scene;
}






/*
Terminate the program
*/
int appTerminate( const char * message )
{
	deallocate();

	glfwTerminate();
	glfwDestroyWindow( _window );

	if( message[0] != '\0' )
		std::cerr << message << std::endl;

	return -1;
}







/*
glfw keyboard callback function
*/
static void keyboardCallback( GLFWwindow * window, int key, int scancode, int action, int mods )
{
	if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
		glfwSetWindowShouldClose( _window, GL_TRUE );
}







/*
Main program entry point
*/
int main( int * argc, char ** argv )
{
	// Initialize glfw
	if( !glfwInit() )
		return appTerminate( "Failed to initialize glfw\n" );

	// Create glfw window
	_window = glfwCreateWindow(
		INITIAL_WINDOW_WIDTH,
		INITIAL_WINDOW_HEIGHT,
		argv[0],
		NULL,
		NULL
		);


	// Verify successful window creation
	if( !_window )
		return appTerminate( "Failed to create glfw window\n" );
		

	// Set the current context
	glfwMakeContextCurrent( _window );


	// Initialize glew
	if( glewInit() != GLEW_OK )
		return appTerminate( "Failed to initialize glew\n" );

	
	// Initialize other GL attributes
	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );


	// Initialize the scene
	_scene = new Scene( _window );
	if( !_scene->initScene() )
		return appTerminate( "Failed to initialize scene\n" );


	// Hook up callbacks
	glfwSetKeyCallback( _window, keyboardCallback );


	// Main loop
	while( !glfwWindowShouldClose( _window ) )
	{
		_scene->processFrame();
		glfwPollEvents();
	}


	// Exit
	appTerminate( "" );
	return 0;
}