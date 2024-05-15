#include "BarnesHut.h"

// Constructor
BarnesHut::BarnesHut(std::vector<std::shared_ptr<Body>>& b) : Algorithm(b)
{

}

void BarnesHut::create()
{
	// Initialize top and bottom bounds
	Vector top = Vector(-INFINITY, -INFINITY, -INFINITY);
	Vector bot = Vector(INFINITY, INFINITY, INFINITY);

	for (auto& b : body)
	{
		// Maximize top bound
		top.x = std::max(top.x, b->position.x);
		top.y = std::max(top.y, b->position.y);
		top.z = std::max(top.z, b->position.z);

		// Minimize lower bound
		bot.x = std::min(bot.x, b->position.x);
		bot.y = std::min(bot.y, b->position.y);
		bot.z = std::min(bot.z, b->position.z);
	}

	// Create new octree
	octree = std::make_unique<Octree>(top, bot);
}

void BarnesHut::build()
{
	// Insert each body into octree
	for (auto& b : body)
	{
		octree->insert(b);
	}
}

void BarnesHut::calculateAcceleration(std::unique_ptr<Octree>& root, std::shared_ptr<Body> b)
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

		// Get reference to bodies
		Body& bm = *b;
		Body& bn = *root->body;

		// Direction vector
		Vector direction = bn.position - bm.position;

		// Distance
		double r = 1 / InverseSquare(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);

		// Force
		double F = (G * bm.mass * bn.mass) / (r * r * r + epsilon);

		// Acceleration
		double a = F / bm.mass;

		bm.acceleration = bm.acceleration + direction * a;

		return;
	}

	// Width of octant
	float width = (root->top.x - root->bot.x) * (root->top.x - root->bot.x);
	// Distance between body and masscenter
	float distance = DistanceSquared(b->position, root->center);

	if (width / distance < (theta * theta))
	{
		// Get reference
		Body& bm = *b;

		// Direction vector
		Vector direction = root->center - bm.position;

		// Distance
		double r = 1 / InverseSquare(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);

		// Force
		double F = (G * bm.mass * root->mass) / (r * r * r + epsilon);

		// Acceleration
		double a = F / bm.mass;

		bm.acceleration = bm.acceleration + direction * a;

		return;
	}
	
	// Calculate acceleration for all children
	for (auto& c : root->child)
	{
		if (c)
		{
			calculateAcceleration(c, b);
		}
	}
}

void BarnesHut::updateAcceleration()
{
	for (auto& b : body)
	{
		if (b->dynamic)
		{
			// Reset acceleration
			b->acceleration = Vector(0,0,0);

			calculateAcceleration(octree, b);
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
}