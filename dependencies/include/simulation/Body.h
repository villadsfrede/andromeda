#ifndef ANDROMEDA_BODY_H
#define ANDROMEDA_BODY_H

#include "Vector.h"

class Body {
public:
	double mass;
	
	Vector position;
	Vector velocity;
	Vector acceleration;

	// if simulated
	bool dynamic;

	// Constructor
	Body(double m, Vector p, Vector v, Vector a, bool d);
};

#endif