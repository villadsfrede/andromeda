#include <iostream>
#include "BarnesHut.h"

BarnesHut::BarnesHut(std::vector<std::shared_ptr<Body>>& b) : Algorithm(b)
{

}

void BarnesHut::construct()
{
	glm::vec3 top = glm::vec3(INFINITY, -INFINITY, INFINITY);
	glm::vec3 bot = glm::vec3(-INFINITY, INFINITY, -INFINITY);

	for (auto& b : body)
	{
		top.x = fminf(top.x, b->position.x);
		top.y = fmaxf(top.y, b->position.y);
		top.z = fminf(top.z, b->position.z);

		bot.x = fmaxf(bot.x, b->position.x);
		bot.y = fminf(bot.y, b->position.y);
		bot.z = fmaxf(bot.z, b->position.z);
	}

	octree = std::make_unique<Octree>(top, bot);

	for (auto& b : body)
	{
		octree->insert(b);
	}

	traverse(octree);
}

void BarnesHut::update()
{
	construct();
}