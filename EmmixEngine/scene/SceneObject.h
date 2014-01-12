#pragma once
#include <iostream>

// GL
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <GL\glew.h>

#ifndef M_PI
#define M_PI 3.141592653589793238
#endif


/*
The SceneObject class is the base class for any object that is to exist within a Scene
*/
class SceneObject
{
public:
	SceneObject( void );
	~SceneObject( void );


	// Mutators
public:
	void move		( const glm::vec3 amount );
	void rotate		( const glm::vec3 amount );


	// Accessors
public:
	const	glm::vec3		getVectorForward	( void );
	const	glm::vec3		getVectorUp			( void );
	const	glm::vec3		getVectorRight		( void );

	const	glm::vec3 *		getPosition			( void );
	const	glm::vec3 *		getRotation			( void );
	const	glm::vec3 *		getScale			( void );
	const	glm::mat4		getModelMatrix		( void );


	// Members
protected:
	glm::vec3 _objPosition;
	glm::vec3 _objRotation;
	glm::vec3 _objScale;
};