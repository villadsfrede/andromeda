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

Vector Normalize(Vector v)
{
	return v / Length(v);
}
