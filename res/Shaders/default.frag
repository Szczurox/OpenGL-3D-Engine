#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// Imports the color from the Vertex Shader
in vec3 color;
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;
// Imports the normal from the Vertex Shader
in vec3 normal;
// Imports the current position from the Vertex Shader
in vec3 curPos;

// Gets the Texture Unit
uniform sampler2D tex0;
// Gets the light color
uniform vec4 lightColor;
// Gets the light position
uniform vec3 lightPos;
// Gets the camera position
uniform vec3 camPos;

void main()
{
	// Ambient lighting
	float ambient = 0.2f;

	// Diffuse lighting
	vec3 nNormal = normalize(normal);
	// Light direction
	vec3 lightDir = normalize(lightPos - curPos);
	float diffuse = max(dot(nNormal, lightDir), 0.0f);

	// Specular lighting
	float specLight = 0.5f;
	// View direction
	vec3 viewDir = normalize(camPos - curPos);
	// Reflection direction
	vec3 reflectDir = reflect(-lightDir, nNormal);
	float specAmount = pow(max(dot(viewDir, reflectDir), 0.0f), 8);
	float specular = specAmount * specLight;

	// outputs final color
	FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient + specular);
}