#version 330 core
out vec4 FragColor;

// Gets a color from the Vertex Shader
in vec3 color;
// Gets texture coordinates from the Vertex Shader
in vec2 texCoord;

// Gets the Texture Unit
uniform sampler2D tex0;

void main()
{
	// Sets object texture
	FragColor = texture(tex0, texCoord);
}