#pragma once
#include "SceneObject.h"

class SceneCamera : public SceneObject
{
public:
	SceneCamera( float fov, float aspectRatio, float zNearClip, float zFarClip );
	~SceneCamera( void );



	// Matrix accessors
public:
	glm::mat4 getViewMatrix( void );
	glm::mat4 getProjectionMatrixPerspective( void );



	// Mutators
public:
	void setFov( float amount );
	void setAspectRatio( float amount );
	void setZNearClip( float amount );
	void setZFarClip( float amount );



	// SceneCamera members
private:
	float
		_fov,
		_aspectRatio,
		_zNearClip,
		_zFarClip;
};