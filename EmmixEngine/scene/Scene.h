#pragma once
#include <iostream>
#include <vector>

// GL
#include <glm\glm.hpp>
#include <GL\glew.h>

// Loaders
#include "..\\LoadShaders.h"

// Scene objects
#include "SceneClock.h"
#include "SceneCamera.h"
#include "Mesh.h"




/*
The Scene class handles all containment and interaction of SceneObjects, including Meshes, Cameras and Lights
glew and glfw are expected to be initialized before any instantiation of a Scene
*/
class Scene
{

	// Initialization
public:
	Scene( GLFWwindow * pWindow );
	~Scene(void);
	bool initScene( void );

private:
	bool loadShaders( void );



	// Main loop
public:
	void processFrame( void );

private:
	void updateScene( void );
	void renderScene( void );



	// Scene Members
private:
	GLFWwindow *		_pWindow;

	SceneClock			_sceneClock;
	SceneCamera			_camera;
	std::vector<Mesh>	_meshes;


	// Shader IDs
private:
	GLuint _ID_program;

	GLuint _ID_matr_model;
	GLuint _ID_matr_view;
	GLuint _ID_matr_projection;
	GLuint _ID_matr_mvp;


	// VAOs / Buffers
private:
	// Vertex Array IDs
	enum VAO_IDs
	{
		_VAOID_Triangle,
		_NumVAOIDs
	};
	GLuint VAOs[_NumVAOIDs];


	// Buffer IDs
	enum Buffers_IDs
	{
		_BuffID_Vertex,
		_BuffID_UV,
		_BuffID_Normal,
		_NumBuffIDs
	};
	GLuint Buffers[_NumBuffIDs];
};

