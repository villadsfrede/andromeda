#ifndef ANDROMEDA_UNIVERSE_H
#define ANDROMEDA_UNIVERSE_H

class Universe {
public:
	float positions[3 * 100] = { 0 };
	float velocities[3 * 100] = { 0 };

	void generate();
};

#endif
