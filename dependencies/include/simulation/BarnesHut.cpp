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

		double r = 1 / InverseSquare(bibj.x * bibj.x + bibj.y * bibj.y + bibj.z * bibj.z);

		double F = (G * bi.mass * bj.mass) / (r * r * r + epsilon);

		double a = F / bi.mass;

		bi.acceleration = bi.acceleration + bibj * a;

		return;
	}

	float width = (root->top.x - root->bot.x) * (root->top.x - root->bot.x);
	float distance = DistanceSquared(b->position, root->center);

	if (width / distance < (theta * theta))
	{
		Body& bi = *b;

		Vector bic = root->center - bi.position;

		double r = 1 / InverseSquare(bic.x * bic.x + bic.y * bic.y + bic.z * bic.z);

		double F = (G * bi.mass * root->mass) / (r * r * r + epsilon);

		double a = F / bi.mass;

		bi.acceleration = bi.acceleration + bic * a;

		return;
	}

	for (auto& c : root->child)
	{
		if (c)
		{
			calculateForce(c, b);
		}
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
		}
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