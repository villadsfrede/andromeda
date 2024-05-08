#include <iostream>
#include "BarnesHut.h"

BarnesHut::BarnesHut(std::vector<std::shared_ptr<Body>>& b) : Algorithm(b)
{

}

void BarnesHut::create()
{
	Vector top = Vector(-INFINITY, -INFINITY, -INFINITY);
	Vector bot = Vector(INFINITY, INFINITY, INFINITY);

	for (auto& b : body)
	{
		top.x = std::max(top.x, b->position.x);
		top.y = std::max(top.y, b->position.y);
		top.z = std::max(top.z, b->position.z);

		bot.x = std::min(bot.x, b->position.x);
		bot.y = std::min(bot.y, b->position.y);
		bot.z = std::min(bot.z, b->position.z);
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
		if (b == root->body)
		{
			return;
		}

		Body& bi = *b;
		Body& bj = *root->body;

		Vector bibj = bj.position - bi.position;

		double r = Distance(bi.position, bj.position) + (epsilon * epsilon);

		double F = G * (bi.mass * bj.mass) / ((r * r) + (epsilon * epsilon));

		double a = F / bi.mass;

		bi.acceleration = bi.acceleration + Normalize(bibj) * a;

		return;
	}

	float width = Distance(root->top, root->bot);
	float distance = Distance(b->position, root->center);

	if (width / distance < theta)
	{
		Body& bi = *b;

		Vector bic = root->center - bi.position;

		double r = Distance(bi.position, root->center);

		double F = G * (bi.mass * root->mass) / ((r * r) + (epsilon * epsilon));

		double a = F / bi.mass;

		bi.acceleration = bi.acceleration + Normalize(bic) * a;

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
		if (b->dynamic)
		{
			b->acceleration = Vector(0,0,0);

			calculateForce(octree, b);
			
			//std::cout << b->acceleration.x << " " << b->acceleration.y << " " << b->acceleration.z << std::endl;
		}
	}
}

void BarnesHut::updateVelocity()
{
	for (auto& b : body)
	{
		b->velocity = b->velocity + b->acceleration * (float)DT;

		//std::cout << b->velocity.x << " " << b->velocity.y << " " << b->velocity.z << std::endl;
	}
}

void BarnesHut::updatePosition()
{
	for (auto& b : body)
	{
		b->position = b->position + b->velocity * (float)DT;

		//std::cout << b->position.x << " " << b->position.y << " " << b->position.z << std::endl;
	}
}

void BarnesHut::update()
{
	create();

	build();

	calculate(octree);

	//std::cout << octree->center.x << " " << octree->center.y << " " << octree->center.z << std::endl;

	updateAcceleration();
	updateVelocity();
	updatePosition();

	//traverse(octree);
}