#version 330 core

// Coordinates
layout (location = 0) in vec3 aPos;
// Normals
layout (location = 1) in vec3 aNormal;
// Colors
layout (location = 2) in vec3 aColor;
// Texture Coordinates
layout (location = 3) in vec2 aTex;


// Outputs the current position for the Fragment Shader
out vec3 curPos;
// Outputs the normal for the Fragment Shader
out vec3 normal;
// Outputs the color for the Fragment Shader
out vec3 color;
// Outputs the texture coordinates to the Fragment Shader
out vec2 texCoord;

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
	// Assigns the normal from the Vertex Data to "normal"
	normal = aNormal;
	// Assigns the colors from the Vertex Data to "color"
	color = aColor;
	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	texCoord = mat2(0.0, -1.0, 1.0, 0.0) * aTex;

	// Outputs the positions of all vertices
	gl_Position = camMatrix * vec4(curPos, 1.0);
}