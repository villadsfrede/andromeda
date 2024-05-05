#ifndef ANDROMEDA_BARNESHUT_H
#define ANDROMEDA_BARNESHUT_H

#include "Algorithm.h"
#include "Octree.h"

class BarnesHut : public Algorithm {
public:
	const float epsilon = 0.5f;
	const float theta = 0.5f;

	std::unique_ptr<Octree> octree;

	BarnesHut(Universe& u);

	void bounds();
	void construct();
	void update() override;
};

#endif