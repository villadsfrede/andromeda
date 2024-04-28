#include <stdlib.h>
#include "Universe.h"

void Universe::generate()
{
	for (unsigned int i = 0; i < 3 * 100; i++)
	{
		bodies[i] = (2 * (float(rand()) / float(RAND_MAX))) - 1;
	}
}