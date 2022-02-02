#version 330 core

// Coordinates
layout (location = 0) in vec3 aPos;

// Gets the camera matrix
uniform mat4 camMatrix;
// Gets the model matrix
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;
uniform mat4 model;


void main()
{
	// Calculates current position
	curPos = vec3(model * translation * -rotation * scale * vec4(aPos, 1.0f));
	// Outputs the positions of all vertices
	gl_Position = camMatrix * vec4(curPos, 1.0);
}