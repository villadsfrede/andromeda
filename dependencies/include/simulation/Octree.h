#ifndef ANDROMEDA_OCTREE_H
#define ANDROMEDA_OCTREE_H

#include <memory>
#include <glm/glm.hpp>

class Octree {
public:
	glm::vec3 top;
	glm::vec3 bot;

	glm::vec3 center;

	float mass;

	bool leaf;

	unsigned short int body = -1;

	std::unique_ptr<Octree> child[8] = { nullptr };

	Octree(glm::vec3 t, glm::vec3 b);

	void insert(float x, float y, float z, unsigned short int index);

	unsigned short int octant(float x, float y, float z);
};

#endif