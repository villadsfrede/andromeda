#ifndef ANDROMEDA_VECTOR_H
#define ANDROMEDA_VECTOR_H

#include <iostream>

class Vector {
public:
	double x, y, z;

	Vector();
	Vector(double x, double y, double z);
	Vector operator + (const Vector v);
	Vector operator - (const Vector v);

	Vector operator * (const double c);
	Vector operator / (const double c);

	bool operator == (const Vector v);
	bool operator != (const Vector v);
};

double Length(const Vector v);
double Distance(const Vector v, const Vector u);
double DistanceSquared(const Vector v, const Vector u);
double ABG(const Vector v);
double InverseSquare(double n);
double FastPow(double a, double b);
Vector Normalize(Vector v);


#endif