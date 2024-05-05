#include "Octree.h"

Octree::Octree(glm::vec3 t, glm::vec3 b)
{
	top = t;
	bot = b;
	center = glm::vec3(0, 0, 0);
	mass = 0;
	leaf = true;
}

unsigned short int Octree::octant(float x, float y, float z)
{
	if ((top.x + bot.x) / 2.0f >= x)
	{
		if ((top.y + bot.y) / 2.0f >= y)
		{
			if ((top.z + bot.z) / 2.0f >= z)
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
			if ((top.z + bot.z) / 2.0f >= z)
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
		if ((top.y + bot.y) / 2.0f >= y)
		{
			if ((top.z + bot.z) / 2.0f >= z)
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
			if ((top.z + bot.z) / 2.0f >= z)
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