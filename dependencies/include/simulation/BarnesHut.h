#ifndef ANDROMEDA_BARNESHUT_H
#define ANDROMEDA_BARNESHUT_H

#include "Constants.h"
#include "Algorithm.h"
#include "Octree.h"

// Extend algorithm
class BarnesHut : public Algorithm {
public:
	const float epsilon = 0.5f;
	const float theta = 1.5f;
	
	// Octree
	std::unique_ptr<Octree> octree = nullptr;

	// Constructor
	BarnesHut(std::vector<std::shared_ptr<Body>>& b);

	void create();
	void build();
	void calculateAcceleration(std::unique_ptr<Octree>& root, std::shared_ptr<Body> b);
	void updateAcceleration();
	void updateVelocity();
	void updatePosition();
	void update() override;
};

#endif