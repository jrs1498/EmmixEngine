#include "SceneCamera.h"

SceneCamera::SceneCamera( float fov, float aspectRatio, float zNearClip, float zFarClip )
	:	_fov			( fov ),
		_aspectRatio	( aspectRatio ),
		_zNearClip		( zNearClip ),
		_zFarClip		( zFarClip )
{
	
}

SceneCamera::~SceneCamera( void )
{
	
}




/*
Calculates and returns this SceneCamera's view matrix according to its orientation
and position within the Scene
*/
glm::mat4 SceneCamera::getViewMatrix( void )
{
	glm::vec3 forwardVector		= getVectorForward();
	glm::vec3 upVector			= getVectorUp();

	return glm::lookAt(
		_objPosition,
		_objPosition + forwardVector,
		upVector
		);
}




/*
Calculates and returns this SceneCamera's perspective projection matrix according
to its attributes
*/
glm::mat4 SceneCamera::getProjectionMatrixPerspective( void )
{
	return glm::perspective(
		_fov,
		_aspectRatio,
		_zNearClip,
		_zFarClip
		);
}