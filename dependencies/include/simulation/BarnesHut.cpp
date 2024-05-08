#include <iostream>
#include "BarnesHut.h"

BarnesHut::BarnesHut(std::vector<std::shared_ptr<Body>>& b) : Algorithm(b)
{

}

void BarnesHut::create()
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

	//std::cout << "__________" << std::endl;
	//std::cout << top.x << " " << top.y << " " << top.z << std::endl;
	//std::cout << bot.x << " " << bot.y << " " << bot.z << std::endl;
	//std::cout << "__________" << std::endl;

	octree = std::make_unique<Octree>(top, bot);
}

void BarnesHut::build()
{
	for (auto& b : body)
	{
		octree->insert(b);
	}
}

void BarnesHut::calculateForce(std::unique_ptr<Octree>& root, std::shared_ptr<Body> b)
{
	if (!root)
	{
		return;
	}

	if (root->body)
	{
		Body& bi = *b;
		Body& bj = *root->body;

		glm::vec3 rij = bj.position - bi.position;

		float r = sqrt((rij.x * rij.x) + (rij.y * rij.y) + (rij.z * rij.z) + (epsilon * epsilon));

		glm::vec3 force = rij * (float)((G * bi.mass * bj.mass) / (r * r * r + (epsilon * epsilon)));

		bi.acceleration = bi.acceleration + (force / bi.mass);
	}

	float width = root->bot.x - root->top.x;
	float distance = glm::distance(b->position, root->center);

	if (width / distance < theta)
	{
		Body& bi = *b;

		glm::vec3 rij = root->center - bi.position;

		float r = sqrt((rij.x * rij.x) + (rij.y * rij.y) + (rij.z * rij.z) + (epsilon * epsilon));

		glm::vec3 force = rij * (float)((6.67E-11 * bi.mass * root->mass) / (r * r * r + (epsilon * epsilon)));

		bi.acceleration = bi.acceleration + (force / bi.mass);

		return;
	}

	for (auto& c : root->child)
	{
		calculateForce(c, b);
	}
}

void BarnesHut::updateAcceleration()
{
	for (auto& b : body)
	{
		b->acceleration = glm::vec3(0, 0, 0);

		calculateForce(octree, b);
	}
}

void BarnesHut::updateVelocity()
{
	for (auto& b : body)
	{
		b->velocity = b->velocity + b->acceleration * (float)DT;
	}
}

void BarnesHut::updatePosition()
{
	for (auto& b : body)
	{
		b->position = b->position + b->velocity * (float)DT;
	}
}

void BarnesHut::update()
{
	create();

	build();

	calculate(octree);

	updateAcceleration();
	updateVelocity();
	updatePosition();

	//traverse(octree);
}