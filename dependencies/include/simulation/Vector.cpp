#include "Vector.h"

Vector::Vector() : x(0), y(0), z(0)
{

}

Vector::Vector(double x, double y, double z) : x(x), y(y), z(z)
{

}

Vector Vector::operator+(const Vector v)
{
	return Vector(x + v.x, y + v.y, z + v.z);
}

Vector Vector::operator-(const Vector v)
{
	return Vector(x - v.x, y - v.y, z - v.z);
}

Vector Vector::operator*(const double c)
{
	return Vector(x * c, y * c, z * c);
}

Vector Vector::operator/(const double c)
{
	return Vector(x / c, y / c, z / c);
}

bool Vector::operator==(const Vector v)
{
	return x == v.x && y == v.y && z == v.z;
}

bool Vector::operator!=(const Vector v)
{
	return x != v.x || y != v.y || z != v.z;
}

double Length(const Vector v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

double Distance(const Vector v, const Vector u)
{
	return sqrt((v.x - u.x) * (v.x - u.x) + (v.y - u.y) * (v.y - u.y) + (v.z - u.z) * (v.z - u.z));
}

double DistanceSquared(const Vector v, const Vector u)
{
	return (v.x - u.x) * (v.x - u.x) + (v.y - u.y) * (v.y - u.y) + (v.z - u.z) * (v.z - u.z);
}

double ABG(const Vector v)
{
	// alpha max plus beta min plus gamma med
	double max = std::max(v.x, std::max(v.y, v.z));
	double min = std::min(v.x, std::min(v.y, v.z));
	double med = std::min(v.x, std::max(v.y, v.z));
	return max * 0.93980863517232523127 + min * 0.29870618761437979596 + med * 0.38928148272372526647;
}

double InverseSquare(double n)
{
	// QUAKE III FAST INVERSE SQUARE

	const float threehalfs = 1.5f;

	float x2 = n * 0.5F;
	float y = n;

	long i = *(long*)&y;

	i = 0x5f3759df - (i >> 1);
	y = *(float*)&i;

	y = y * (threehalfs - (x2 * y * y));

	return y;
}

Vector Normalize(Vector v)
{
	return v * InverseSquare(v.x * v.x + v.y  * v.y + v.z * v.z);
}
