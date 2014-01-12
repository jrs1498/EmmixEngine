#include "Mesh.h"


Mesh::Mesh( std::vector<glm::vec3> vertPositions )
	: _vertPositions( vertPositions )
{
}


Mesh::~Mesh(void)
{
}



// Vertex accessors
std::vector<glm::vec3>		* Mesh::getVertices		( void )		{ return &_vertPositions; }
std::vector<glm::vec3>		* Mesh::getUVs			( void )		{ return &_vertUVs; }
std::vector<glm::vec3>		* Mesh::getNormals		( void )		{ return &_vertNormals; }