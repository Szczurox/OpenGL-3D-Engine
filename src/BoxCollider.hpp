#ifndef BOX_COLLIDER_CLASS_H
#define BOX_COLLIDER_CLASS_H

#include<string>
#include<vector>

#include"Object.hpp"

// Object, allows to combine collider with texture
class BoxCollider {
	public:
		// Collider parmeters
		glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
		GLfloat width = 0.2f;
		GLfloat height = 0.2f;
		GLfloat depth = 0.2f;

		// Constructors
		BoxCollider() {}; // Empty
		BoxCollider(GLfloat width, GLfloat height, GLfloat depth); // Cuboid collider constructor
		BoxCollider(GLfloat width); // Cube collider constructor
	private:
		GLuint colliderIndices[36] = {
			0, 1, 2,
			0, 2, 3,
			0, 4, 7,
			0, 7, 3,
			3, 7, 6,
			3, 6, 2,
			2, 6, 5,
			2, 5, 1,
			1, 5, 4,
			1, 4, 0,
			4, 5, 6,
			4, 6, 7
		};
};

#endif