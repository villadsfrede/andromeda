#ifndef ANDROMEDA_OCTREE_H
#define ANDROMEDA_OCTREE_H

#include <memory>
#include <glm/glm.hpp>
#include "Body.h"

class Octree {
public:
	glm::vec3 top;	// UPPER BOUND
	glm::vec3 bot;	// LOWER BOUND

	glm::vec3 center = glm::vec3(0,0,0);

	float mass = 0;

	bool leaf = true;

	std::shared_ptr<Body> body = nullptr;

	std::unique_ptr<Octree> child[8];


	Octree(glm::vec3 t, glm::vec3 b);
	~Octree();

	unsigned short int octant(glm::vec3 p);
	void insert(std::shared_ptr<Body> b);
	friend void updatemasscenter(std::unique_ptr<Octree>& root);
	friend void traverse(std::unique_ptr<Octree>& root);
};

#endif