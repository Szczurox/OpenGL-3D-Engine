#version 330 core

// Outputs colors
out vec4 FragColor;

// Imports the current position from the Vertex Shader
in vec3 curPos;
// Imports the normal from the Vertex Shader
in vec3 normal;
// Imports the color from the Vertex Shader
in vec3 color;
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;


// Gets the Texture Units
uniform sampler2D diffuse0;
uniform sampler2D specular0;
// Gets the color of the light
uniform vec4 lightColor;
// Gets the position of the light
uniform vec3 lightPos;
// Gets the position of the camera
uniform vec3 camPos;


// Point light
vec4 pointLight() {	
	// used in two variables so I calculate it here to not have to do it twice
	vec3 lightVec = lightPos - curPos;

	// Distance from the light source 
	float dist = length(lightVec);
	// Quadratic term
	float a = 0.7f;
	// Linear term
	float b = 0.1f;
	// Light intensity
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

	// ambient lighting
	float ambient = 0.2f;

	// Diffuse lighting
	vec3 nNormal = normalize(normal);
	// Light direction
	vec3 lightDir = normalize(lightVec);
	float diffuse = max(dot(nNormal, lightDir), 0.0f);

	// Specular lighting
	float specLight = 0.5f;
	// View direction
	vec3 viewDir = normalize(camPos - curPos);
	// Reflection direction
	vec3 reflectDir = reflect(-lightDir, nNormal);
	float specAmount = pow(max(dot(viewDir, reflectDir), 0.0f), 16);
	float specular = specAmount * specLight;

	return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightColor;
}

// Directional light
vec4 dirLight() {
	// ambient lighting
	float ambient = 0.2f;

	// Diffuse lighting
	vec3 nNormal = normalize(normal);
	// Light direction
	vec3 lightDir = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(dot(nNormal, lightDir), 0.0f);

	// Specular lighting
	float specLight = 0.5f;
	// View direction
	vec3 viewDir = normalize(camPos - curPos);
	// Reflection direction
	vec3 reflectDir = reflect(-lightDir, nNormal);
	float specAmount = pow(max(dot(viewDir, reflectDir), 0.0f), 16);
	float specular = specAmount * specLight;

	return (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * lightColor;
}

// Spot light
vec4 spotLight() {
	// Lowest light cosine
	float outerCone = 0.90f;
	// Max light cosine
	float innerCone = 0.95f;

	// ambient lighting
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
	float specAmount = pow(max(dot(viewDir, reflectDir), 0.0f), 16);
	float specular = specAmount * specLight;

	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDir);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightColor;
}

void main() {
	// Outputs the final texture
	FragColor = pointLight();
}