#ifndef GAME_OBJECT_CLASS_H
#define GAME_OBJECT_CLASS_H

#include<string>
#include<vector>

#include"Mesh.hpp"
#include"ColliderMesh.hpp"
#include"Camera.hpp"

class GameObject {
public:
	std::vector<GLfloat> position;

	Mesh textureMesh;
	ColliderMesh colliderMesh;

	GameObject();
	GameObject(std::vector<GLfloat> pos, Mesh mesh, ColliderMesh collider, Shader shader);

	void AddMesh();
	void AddColiderMesh();

	void Move(glm::vec3 coordinates);

};

#endif
