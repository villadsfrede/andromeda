#ifndef ANDROMEDA_DIRECTSUM_H
#define ANDROMEDA_DIRECTSUM_H

#include "Config.h"
#include "Algorithm.h"

class DirectSum : public Algorithm {
private:
	const float epsilon = 0.5f;

public:
	DirectSum(std::vector<std::shared_ptr<Body>>& b);

	void calculateAcceleration(std::shared_ptr<Body> m, std::shared_ptr<Body> n);
	void updateAcceleration();
	void updateVelocity();
	void updatePosition();
	void update() override;
};

#endif