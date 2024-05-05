#include <iostream>
#include "BarnesHut.h"

BarnesHut::BarnesHut(Universe& u) : Algorithm(u)
{

}

void BarnesHut::bounds()
{
	
}

void BarnesHut::construct()
{
	glm::vec3 top = glm::vec3(-INFINITY, -INFINITY, -INFINITY);
	glm::vec3 bot = glm::vec3(INFINITY, INFINITY, INFINITY);

	for (unsigned int i = 0; i < universe.objects; i++)
	{
		top.x = fmaxf(top.x, universe.posx[i]);
		top.y = fmaxf(top.y, universe.posy[i]);
		top.z = fmaxf(top.z, universe.posz[i]);

		bot.x = fminf(bot.x, universe.posx[i]);
		bot.y = fminf(bot.y, universe.posy[i]);
		bot.z = fminf(bot.z, universe.posz[i]);
	}

	octree = std::make_unique<Octree>(top, bot);

	for (unsigned int i = 0; i < universe.objects; i++)
	{

	}
}

void BarnesHut::update()
{

}