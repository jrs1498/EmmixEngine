#include "SceneObject.h"

SceneObject::SceneObject( void )
	:	_objPosition	( glm::vec3( 0.0f ) ),
		_objRotation	( glm::vec3( 0.0f ) ),
		_objScale		( glm::vec3( 1.0f ) )
{
}

SceneObject::~SceneObject( void )
{
	
}


// Mutators
void SceneObject::move( const glm::vec3 amount )
{
	_objPosition += amount;
}

void SceneObject::rotate( const glm::vec3 amount )
{
	_objRotation += amount;
}


// Accessors
const glm::vec3 SceneObject::getVectorForward( void )
{
	return glm::vec3(
		cos( _objRotation.y ) * sin( _objRotation.x ),
		sin( _objRotation.y ),
		cos( _objRotation.y ) * cos( _objRotation.x )
		);
}

const glm::vec3 SceneObject::getVectorUp( void )
{
	return glm::cross(
		getVectorForward(),
		getVectorRight()
		);
}

const glm::vec3 SceneObject::getVectorRight( void )
{
	return glm::vec3(
		sin( _objRotation.y - M_PI * 0.5f ),
		0,
		cos( _objRotation.x - M_PI * 0.5f )
		);
}




const glm::vec3 * SceneObject::getPosition( void )
{ return &_objPosition; }

const glm::vec3 * SceneObject::getRotation( void )
{ return &_objRotation; }

const glm::vec3 * SceneObject::getScale( void )
{ return &_objScale; }

const glm::mat4 SceneObject::getModelMatrix( void )
{
	const glm::mat4 modelMatrix = 
		glm::scale( _objScale ) *
		glm::translate( _objPosition );

	return modelMatrix;
}