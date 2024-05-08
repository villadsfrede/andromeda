#ifndef ANDROMEDA_OCTREE_H
#define ANDROMEDA_OCTREE_H

#include <memory>
#include "Vector.h"
#include "Body.h"

class Octree {
public:
	Vector top;	// UPPER BOUND
	Vector bot;	// LOWER BOUND

	Vector center;

	float mass;

	bool leaf;

	std::shared_ptr<Body> body;

	std::unique_ptr<Octree> child[8] = { nullptr };


	Octree(Vector t, Vector b);
	~Octree();

	unsigned short int octant(Vector p);
	void insert(std::shared_ptr<Body> b);
	friend void calculate(std::unique_ptr<Octree>& root);
	friend void traverse(std::unique_ptr<Octree>& root);
};

#endif