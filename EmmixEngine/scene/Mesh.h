#pragma once
#include <vector>

// Inheritance
#include "SceneObject.h"


/*
The Mesh class specifies information about any scene object which will be rendered
using vertices
*/
class Mesh : public SceneObject
{
public:
	Mesh( std::vector<glm::vec3> vertices );
	~Mesh(void);


	// Vertex accessors
public:
	std::vector<glm::vec3>		* getVertices		( void );
	std::vector<glm::vec3>		* getUVs			( void );
	std::vector<glm::vec3>		* getNormals		( void );


	// Mesh members
private:
	std::vector<glm::vec3>		_vertPositions;
	std::vector<glm::vec3>		_vertUVs;
	std::vector<glm::vec3>		_vertNormals;
};

