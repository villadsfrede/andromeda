#ifndef ANDROMEDA_ALGORITHM_H
#define ANDROMEDA_ALGORITHM_H

#include "Universe.h"

class Algorithm {
public:
	Universe& universe;

	Algorithm(Universe& u);

	virtual void update() = 0;
};

#endif