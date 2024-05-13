#ifndef ANDROMEDA_BARNESHUT_H
#define ANDROMEDA_BARNESHUT_H

#include "Algorithm.h"
#include "Octree.h"
#include "Config.h"

class BarnesHut : public Algorithm {
public:
	const float epsilon = 0.5f;
	const float theta = 1.5f;

	std::unique_ptr<Octree> octree = nullptr;

	BarnesHut(std::vector<std::shared_ptr<Body>>& b);

	void create();
	void build();
	void calculateForce(std::unique_ptr<Octree>& root, std::shared_ptr<Body> b);
	void updateAcceleration();
	void updateVelocity();
	void updatePosition();
	void update() override;
};

#endif