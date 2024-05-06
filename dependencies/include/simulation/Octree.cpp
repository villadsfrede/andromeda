#include "Octree.h"

Octree::Octree(glm::vec3 t, glm::vec3 b)
{
	top = t;
	bot = b;
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
}

void Octree::insert(std::shared_ptr<Body> b)
{
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

	if (child[oct] == nullptr)
	{
		float width = abs(top.x) + abs(bot.x);
		float height = abs(top.y) + abs(bot.y);
		float depth = abs(top.z) + abs(bot.z);

		glm::vec3 c = glm::vec3(bot.x + width / 2, bot.y + height / 2, bot.z + depth / 2);

		switch (oct)
		{
		case 0:
			child[oct] = std::make_unique<Octree>(c, glm::vec3(bot.x, bot.y, bot.z));
		case 1:
			child[oct] = std::make_unique<Octree>(c, glm::vec3(bot.x + width, bot.y, bot.z));
		case 2:
			child[oct] = std::make_unique<Octree>(glm::vec3(bot.x, bot.y + height, bot.z), c);
		case 3:
			child[oct] = std::make_unique<Octree>(glm::vec3(bot.x + width, bot.y + height, bot.z), c);
		case 4:
			child[oct] = std::make_unique<Octree>(c, glm::vec3(bot.x, bot.y, bot.z + depth));
		case 5:
			child[oct] = std::make_unique<Octree>(c, glm::vec3(bot.x + width, bot.y, bot.z + depth));
		case 6:
			child[oct] = std::make_unique<Octree>(glm::vec3(bot.x, bot.y + height, bot.z + depth), c);
		case 7:
			child[oct] = std::make_unique<Octree>(glm::vec3(bot.x + width, bot.y + height, bot.z + depth), c);
		}
		child[oct]->insert(b);
	}
}

void traverse(std::unique_ptr<Octree>& root)
{
	if (!root)
	{
		return;
	}
	
	std::cout << "-------------------" << std::endl;
	std::cout << "TOP BOUND" << std::endl;
	std::cout << root->top.x << std::endl;
	std::cout << root->top.y << std::endl;
	std::cout << root->top.z << std::endl;
	std::cout << "BOT BOUND" << std::endl;
	std::cout << root->bot.x << std::endl;
	std::cout << root->bot.y << std::endl;
	std::cout << root->bot.z << std::endl;

	for (auto& c : root->child)
	{
		traverse(c);
	}
}

/*
void Octree::insert(float x, float y, float z, unsigned short int index)
{
	if (leaf)
	{
		body = index;
		return;
	}

	

	leaf = false;

	unsigned short int o = octant(x, y, z);

	if (child[o] == nullptr)
	{
		float width = top.x + bot.x;
		float height = top.y + bot.y;
		float depth = top.z + bot.z;

		glm::vec3 c = glm::vec3(bot.x + width / 2, bot.y + height / 2, bot.z + depth / 2);

		switch (o)
		{
		case 0:
			child[o] = std::make_unique<Octree>(c, glm::vec3(bot.x, bot.y, bot.z));
		case 1:
			child[o] = std::make_unique<Octree>(c, glm::vec3(bot.x + width, bot.y, bot.z));
		case 2:
			child[o] = std::make_unique<Octree>(glm::vec3(bot.x, bot.y + height, bot.z), c);
		case 3:
			child[o] = std::make_unique<Octree>(glm::vec3(bot.x + width, bot.y + height, bot.z), c);
		case 4:
			child[o] = std::make_unique<Octree>(c, glm::vec3(bot.x, bot.y, bot.z + depth));
		case 5:
			child[o] = std::make_unique<Octree>(c, glm::vec3(bot.x + width, bot.y, bot.z + depth));
		case 6:
			child[o] = std::make_unique<Octree>(glm::vec3(bot.x, bot.y + height, bot.z + depth), c);
		case 7:
			child[o] = std::make_unique<Octree>(glm::vec3(bot.x + width, bot.y + height, bot.z + depth), c);
		}

		child[o]->insert(x, y, z, index);
	}
}
*/