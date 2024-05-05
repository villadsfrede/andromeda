#ifndef ANDROMEDA_ALGORITHM_H
#define ANDROMEDA_ALGORITHM_H

#include <memory>
#include <vector>

#include "Body.h"

class Algorithm {
public:
	std::vector<std::shared_ptr<Body>>& body;

	Algorithm(std::vector<std::shared_ptr<Body>>& b);

	virtual void update() = 0;
};

#endif