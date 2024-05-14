#ifndef ANDROMEDA_OCTREE_H
#define ANDROMEDA_OCTREE_H

#include <memory>
#include <iostream>
#include "Vector.h"
#include "Body.h"

class Octree {
public:
	// Bounds
	Vector top;
	Vector bot;

	// Center of mass
	Vector center;

	// Total mass
	float mass;

	// if contains body
	bool leaf;

	// Contained body
	std::shared_ptr<Body> body;

	// Child nodes
	std::unique_ptr<Octree> child[8] = { nullptr };

	// Constructor
	Octree(Vector t, Vector b);

	// Get octant at position
	unsigned short int octant(Vector p);
	// Insert body
	void insert(std::shared_ptr<Body> b);
	// Calculate total mass and center of mass for each node in tree
	friend void calculate(std::unique_ptr<Octree>& root);
};

#endif