#ifndef ANDROMEDA_ALGORITHM_H
#define ANDROMEDA_ALGORITHM_H

#include <memory>
#include <vector>

#include "Body.h"

class Algorithm {
public:
	// Vector of pointers to bodies
	std::vector<std::shared_ptr<Body>>& body;

	// Constructor
	Algorithm(std::vector<std::shared_ptr<Body>>& b);

	virtual void update() = 0;
};

#endif