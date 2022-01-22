#version 330 core
// Coordinates
layout (location = 0) in vec3 aPos;
// Color
layout (location = 1) in vec3 aColor;
// Tex
layout (location = 2) in vec2 aTex;

// Outputs a color for the Fragment Shader
out vec3 color;

out vec2 texCoord;

uniform float scale;

void main()
{
	gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
	// Assigns the colors from the Vertex Data to "color"
	color = aColor;
	texCoord = aTex;
};
