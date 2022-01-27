#include"GameObject.hpp"

GameObject::GameObject(std::vector<GLfloat> pos, Mesh mesh, ColliderMesh collider, Shader shader) {
	GameObject::position = pos;
	GameObject::textureMesh = mesh;
	GameObject::colliderMesh = collider;
}