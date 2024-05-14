#ifndef ANDROMEDA_VECTOR_H
#define ANDROMEDA_VECTOR_H

#include <cmath>

class Vector {
public:
	// components
	double x, y, z;

	// Constructors
	Vector();
	Vector(double x, double y, double z);

	// Vector functions
	Vector operator + (const Vector v);
	Vector operator - (const Vector v);

	// Number functions
	Vector operator * (const double c);
	Vector operator / (const double c);

	// Boolean operations
	bool operator == (const Vector v);
	bool operator != (const Vector v);
};

double Length(const Vector v);
double Distance(const Vector v, const Vector u);
double DistanceSquared(const Vector v, const Vector u);
double InverseSquare(double n);
Vector Normalize(Vector v);


#endif