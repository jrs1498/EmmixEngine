#version 430 core

// Input vertex attributes
layout( location = 0 ) in vec3 vertexPosition_modelspace;



// Uniform values
uniform mat4 matr_model;
uniform mat4 matr_view;
uniform mat4 matr_projection;
uniform mat4 matr_mvp;



void main()
{
	gl_Position = matr_mvp * vec4( vertexPosition_modelspace, 1 );
}