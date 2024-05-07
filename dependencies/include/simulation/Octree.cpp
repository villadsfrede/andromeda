#include "Octree.h"

Octree::Octree(glm::vec3 t, glm::vec3 b)
{
	Octree::top = t;
	Octree::bot = b;
	center = glm::vec3(-1, -1, -1);
	mass = 0;
	leaf = true;
	body = nullptr;
}

Octree::~Octree()
{

}

unsigned short int Octree::octant(glm::vec3 p)
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
	std::cout << "OUT OF BOUNDS" << std::endl;
}

void Octree::insert(std::shared_ptr<Body> b)
{
	//std::cout << std::endl;
	//std::cout << "inserting: " << b->position.x << " " << b->position.y << " " << b->position.z << std::endl;
	//std::cout << "TOP: " << top.x << " " << top.y << " " << top.z << std::endl;
	//std::cout << "BOT: " << bot.x << " " << bot.y << " " << bot.z << std::endl;
	//std::cout << "OCTANT: " << octant(b->position) << std::endl;
	//std::cout << std::endl;

	if (b == nullptr)
	{
		return;
	}

	if (body == nullptr && leaf)
	{
		body = b;
		return;
	}

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

	if (oct == 0)
	{
		if (child[0] == nullptr)
		{
			child[0] = std::make_unique<Octree>(glm::vec3((top.x + bot.x) / 2, (top.y + bot.y) / 2, (top.z + bot.z) / 2), glm::vec3(bot.x, bot.y, bot.z));
		}
		child[0]->insert(b);
	}
	else if (oct == 1)
	{
		if (child[1] == nullptr)
		{
			child[1] = std::make_unique<Octree>(glm::vec3(top.x, (top.y + bot.y) / 2, (top.z + bot.z) / 2), glm::vec3((top.x + bot.x) / 2, bot.y, bot.z));
		}
		child[1]->insert(b);
	}
	else if (oct == 2)
	{
		if (child[2] == nullptr)
		{
			child[2] = std::make_unique<Octree>(glm::vec3((top.x + bot.x) / 2, top.y, (top.z + bot.z) / 2), glm::vec3(bot.x, (top.y + bot.y) / 2, bot.z));
		}
		child[2]->insert(b);
	}
	else if (oct == 3)
	{
		if (child[3] == nullptr)
		{
			child[3] = std::make_unique<Octree>(glm::vec3(top.x, top.y, (top.z + bot.z) / 2), glm::vec3((top.x + bot.x) / 2, (top.y + bot.y) / 2, bot.z));
		}
		child[3]->insert(b);
	}
	else if (oct == 4)
	{
		if (child[4] == nullptr)
		{
			child[4] = std::make_unique<Octree>(glm::vec3((top.x + bot.x) / 2, (top.y + bot.y) / 2, top.z), glm::vec3(bot.x, bot.y, (top.z + bot.z) / 2));
		}
		child[4]->insert(b);
	}
	else if (oct == 5)
	{
		if (child[5] == nullptr)
		{
			child[5] = std::make_unique<Octree>(glm::vec3(top.x, (top.y + bot.y) / 2, top.z), glm::vec3((top.x + bot.x) / 2, bot.y, (top.z + bot.z) / 2));
		}
		child[5]->insert(b);
	}
	else if (oct == 6)
	{
		if (child[6] == nullptr)
		{
			child[6] = std::make_unique<Octree>(glm::vec3((top.x + bot.x) / 2, top.y, top.z), glm::vec3(bot.x, (top.y + bot.y) / 2, (top.z + bot.z) / 2));
		}
		child[6]->insert(b);
	}
	else if (oct == 7)
	{
		if (child[7] == nullptr)
		{
			child[7] = std::make_unique<Octree>(glm::vec3(top.x, top.y, top.z), glm::vec3((top.x + bot.x) / 2, (top.y + bot.y) / 2, (top.z + bot.z) / 2));
		}
		child[7]->insert(b);
	}
}

void updatemasscenter(std::unique_ptr<Octree>& root)
{

	if (!root)
	{
		return;
	}

	if (root->body)
	{
		root->mass = root->body->mass;
		root->center = root->body->position;
		return;
	}

	for (auto& c : root->child)
	{
		updatemasscenter(c);
	}

	float mass = 0;

	for (auto& c : root->child)
	{
		if (c)
		{
			mass = mass + c->mass;
		}
	}

	root->mass = mass;
}

void traverse(std::unique_ptr<Octree>& root)
{
	if (!root)
	{
		return;
	}

	std::cout << "MASS: " << root->mass << std::endl;

	for (auto& c : root->child)
	{
		if (c)
		{
			traverse(c);
		}
	}
}
