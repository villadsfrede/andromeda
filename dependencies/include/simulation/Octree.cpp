#include "Octree.h"

// Constructor
Octree::Octree(Vector t, Vector b)
{
	top = t;
	bot = b;
	center = Vector(0, 0, 0);
	mass = 0;
	leaf = true;
	body = nullptr;
}

unsigned short int Octree::octant(Vector p)
{
	if ((top.x + bot.x) / 2.0f >= p.x)
	{
		if ((top.y + bot.y) / 2.0f >= p.y)
		{
			if ((top.z + bot.z) / 2.0f >= p.z)
			{
				return 0;
			}
			else
			{
				return 4;
			}
		}
		else
		{
			if ((top.z + bot.z) / 2.0f >= p.z)
			{
				return 2;
			}
			else
			{
				return 6;
			}
		}
	}
	else
	{
		if ((top.y + bot.y) / 2.0f >= p.y)
		{
			if ((top.z + bot.z) / 2.0f >= p.z)
			{
				return 1;
			}
			else
			{
				return 5;
			}
		}
		else
		{
			if ((top.z + bot.z) / 2.0f >= p.z)
			{
				return 3;
			}
			else
			{
				return 7;
			}
		}
	}

	// Position is not in bounds
	std::cout << "OUT OF BOUNDS" << std::endl;
}

void Octree::insert(std::shared_ptr<Body> b)
{
	if (b == nullptr)
	{
		return;
	}

	// insert body
	if (body == nullptr && leaf)
	{
		body = b;
		return;
	}

	// remove body and insert it again
	if (body != nullptr)
	{
		if (body == b)
		{
			body = nullptr;
		}
		else
		{
			this->insert(body);
		}
	}

	leaf = false;

	int oct = octant(b->position);

	// Create new child in given octant
	if (oct == 0)
	{
		if (child[0] == nullptr)
		{
			child[0] = std::make_unique<Octree>(Vector((top.x + bot.x) / 2, (top.y + bot.y) / 2, (top.z + bot.z) / 2), Vector(bot.x, bot.y, bot.z));
		}
		child[0]->insert(b);
	}
	else if (oct == 1)
	{
		if (child[1] == nullptr)
		{
			child[1] = std::make_unique<Octree>(Vector(top.x, (top.y + bot.y) / 2, (top.z + bot.z) / 2), Vector((top.x + bot.x) / 2, bot.y, bot.z));
		}
		child[1]->insert(b);
	}
	else if (oct == 2)
	{
		if (child[2] == nullptr)
		{
			child[2] = std::make_unique<Octree>(Vector((top.x + bot.x) / 2, top.y, (top.z + bot.z) / 2), Vector(bot.x, (top.y + bot.y) / 2, bot.z));
		}
		child[2]->insert(b);
	}
	else if (oct == 3)
	{
		if (child[3] == nullptr)
		{
			child[3] = std::make_unique<Octree>(Vector(top.x, top.y, (top.z + bot.z) / 2), Vector((top.x + bot.x) / 2, (top.y + bot.y) / 2, bot.z));
		}
		child[3]->insert(b);
	}
	else if (oct == 4)
	{
		if (child[4] == nullptr)
		{
			child[4] = std::make_unique<Octree>(Vector((top.x + bot.x) / 2, (top.y + bot.y) / 2, top.z), Vector(bot.x, bot.y, (top.z + bot.z) / 2));
		}
		child[4]->insert(b);
	}
	else if (oct == 5)
	{
		if (child[5] == nullptr)
		{
			child[5] = std::make_unique<Octree>(Vector(top.x, (top.y + bot.y) / 2, top.z), Vector((top.x + bot.x) / 2, bot.y, (top.z + bot.z) / 2));
		}
		child[5]->insert(b);
	}
	else if (oct == 6)
	{
		if (child[6] == nullptr)
		{
			child[6] = std::make_unique<Octree>(Vector((top.x + bot.x) / 2, top.y, top.z), Vector(bot.x, (top.y + bot.y) / 2, (top.z + bot.z) / 2));
		}
		child[6]->insert(b);
	}
	else if (oct == 7)
	{
		if (child[7] == nullptr)
		{
			child[7] = std::make_unique<Octree>(Vector(top.x, top.y, top.z), Vector((top.x + bot.x) / 2, (top.y + bot.y) / 2, (top.z + bot.z) / 2));
		}
		child[7]->insert(b);
	}
}

void calculate(std::unique_ptr<Octree>& root)
{

	if (!root)
	{
		return;
	}

	// root contains body
	if (root->body)
	{
		// Set root mass and center to body mass and position
		root->mass = root->body->mass;
		root->center = root->body->position;
		return;
	}

	// Calculate each child
	for (auto& c : root->child)
	{
		calculate(c);
	}

	double mass = 0;
	Vector center = Vector(0, 0, 0);

	// Add mass and center of mass from children
	for (auto& c : root->child)
	{
		if (c)
		{
			mass = mass + c->mass;
			center = center + c->center * c->mass;
		}
	}

	root->mass = mass;
	root->center = center / mass;
}

