#ifndef ANDROMEDA_OCTREE_H
#define ANDROMEDA_OCTREE_H

#include <memory>
#include <glm/glm.hpp>
#include "Body.h"

class Octree {
public:
	glm::vec3 top;	// UPPER BOUND
	glm::vec3 bot;	// LOWER BOUND

	glm::vec3 center;

	float mass;

	bool leaf;

	std::shared_ptr<Body> body;

	std::unique_ptr<Octree> child[8] = { nullptr };


	Octree(glm::vec3 t, glm::vec3 b);
	~Octree();

	unsigned short int octant(glm::vec3 p);
	void insert(std::shared_ptr<Body> b);
	friend void calculate(std::unique_ptr<Octree>& root);
	friend void traverse(std::unique_ptr<Octree>& root);
};

#endif