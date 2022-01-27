#include"Object.hpp"

// Object with only 1 mesh
Object::Object(Shader& shader, Mesh& mesh, std::string type) {
	// Sets type inside the Object so that other functions can use it 
	Object::type = type;
	// Activates the shader to output the model to the shader
	shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	// Sets Object Meshes and Shaders so that the other functions can use them
	if (type == "model") {
		modelMesh = mesh;
		modelShader = shader;
		return;
	}
	else {
		colliderMesh = mesh;
		colliderShader = shader;
		return;
	}
	// Outputs an error if Object type is wrong
	std::cout << "OBJECT_TYPE_ERROR for type: " << type << ", type can only be model/shader\n" << std::endl;
}

// Object with collider and model
Object::Object(Shader& modelShader, Mesh& mesh, Shader& colliderShader, Mesh& collider)
	: modelShader(modelShader), modelMesh(mesh), colliderShader(colliderShader), colliderMesh(collider) {
	modelShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	colliderShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(colliderShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
}

// Moves the Object to the specified coordinates
void Object::Move(glm::vec3 coordinates) {
	// Translates the model position to the new one
	model = glm::translate(model, coordinates);
	position = coordinates;
	// Outputs the model to the shaders depending on the type of object
	if (type == "model" || type == "both") {
		modelShader.Activate();
		glUniformMatrix4fv(glGetUniformLocation(modelShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	}
	if (type == "collider" || type == "both") {
		colliderShader.Activate();
		glUniformMatrix4fv(glGetUniformLocation(colliderShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	}
}

// Sets Object's color
void Object::Color(glm::vec4 color, const GLchar* uniform) {
	modelShader.Activate();
	// Exports the color to the Fragment Shader
	glUniform4f(glGetUniformLocation(modelShader.ID, uniform), color.x, color.y, color.z, color.w);
}

void Object::Instantiate(Camera& camera) {
	// Renders object
	modelMesh.Draw(modelShader, camera);
}