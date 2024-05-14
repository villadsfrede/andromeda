#include "DirectSum.h"

DirectSum::DirectSum(std::vector<std::shared_ptr<Body>>& b) : Algorithm(b)
{

}

void DirectSum::calculateAcceleration(std::shared_ptr<Body> m, std::shared_ptr<Body> n)
{
	if (m == n)
	{
		return;
	}

	Body& bm = *m;
	Body& bn = *n;

	Vector direction = bn.position - bm.position;

	double r = 1 / InverseSquare(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);

	double F = (G * bm.mass * bn.mass) / (r * r * r + epsilon);

	double a = F / bm.mass;

	bm.acceleration = bm.acceleration + direction * a;

	return;
}

void DirectSum::updateAcceleration()
{
	for (auto& i : body)
	{
		if (i->dynamic)
		{
			i->acceleration = Vector(0, 0, 0);

			for (auto& j : body)
			{
				calculateAcceleration(i, j);
			}
		}
	}
}

void DirectSum::updateVelocity()
{
	for (auto& b : body)
	{
		b->velocity = b->velocity + b->acceleration * (float)DT;
	}
}

void DirectSum::updatePosition()
{
	for (auto& b : body)
	{
		b->position = b->position + b->velocity * (float)DT;
	}
}

void DirectSum::update()
{
	updateAcceleration();
	updateVelocity();
	updatePosition();
}