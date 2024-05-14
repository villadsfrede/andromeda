#include "Vector.h"

// Empty vector
Vector::Vector() : x(0), y(0), z(0)
{

}

// Vector with parameters
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
	// Return length of vector
	return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

double Distance(const Vector v, const Vector u)
{
	// Return distance between positions
	return std::sqrt((v.x - u.x) * (v.x - u.x) + (v.y - u.y) * (v.y - u.y) + (v.z - u.z) * (v.z - u.z));
}

double DistanceSquared(const Vector v, const Vector u)
{
	// Return distance squared between positions
	return (v.x - u.x) * (v.x - u.x) + (v.y - u.y) * (v.y - u.y) + (v.z - u.z) * (v.z - u.z);
}


double InverseSquare(double n)
{
	// QUAKE III FAST INVERSE SQUARE
	// https://en.wikipedia.org/wiki/Fast_inverse_square_root

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
	// Return normalized vector
	return v * InverseSquare(v.x * v.x + v.y  * v.y + v.z * v.z);
}
