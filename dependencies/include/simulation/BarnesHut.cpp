#include <iostream>
#include "BarnesHut.h"

BarnesHut::BarnesHut(std::vector<std::shared_ptr<Body>>& b) : Algorithm(b)
{

}

void BarnesHut::construct()
{
	glm::vec3 top = glm::vec3(-INFINITY, -INFINITY, -INFINITY);
	glm::vec3 bot = glm::vec3(INFINITY, INFINITY, INFINITY);

	for (auto& b : body)
	{
		top.x = fmaxf(top.x, b->position.x);
		top.y = fmaxf(top.y, b->position.y);
		top.z = fmaxf(top.z, b->position.z);

		bot.x = fminf(bot.x, b->position.x);
		bot.y = fminf(bot.y, b->position.y);
		bot.z = fminf(bot.z, b->position.z);
	}

	std::cout << top.x << " " << top.y << " " << top.z << std::endl;
	std::cout << bot.x << " " << bot.y << " " << bot.z << std::endl;

	//octree = std::make_unique<Octree>(top, bot);
}

void BarnesHut::update()
{
	construct();
}