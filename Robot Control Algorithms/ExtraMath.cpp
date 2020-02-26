#include "ExtraMath.h"



std::array<double, 3> SphericalCoordinate::toArray()
{
	return {magnitude, polarAngle, azimuthalAngle};
}

void SphericalCoordinate::operator=(const CartesianCoordinate& cartesianCoordinate) {
	if (cartesianCoordinate.x == 0 && cartesianCoordinate.y == 0 && cartesianCoordinate.z == 0) 
	{
		magnitude = 0;
		polarAngle = 0;
		azimuthalAngle = 0;
	}
	else
	{
		magnitude = sqrt(pow(cartesianCoordinate.x, 2) + pow(cartesianCoordinate.y, 2) + pow(cartesianCoordinate.z, 2));
		polarAngle = atan2(cartesianCoordinate.y, cartesianCoordinate.x);
		azimuthalAngle = atan2(sqrt(pow(cartesianCoordinate.x, 2) + pow(cartesianCoordinate.y, 2)), cartesianCoordinate.z);
	}

}

void SphericalCoordinate::operator=(const SphericalCoordinate& other)
{
	magnitude = other.magnitude;
	polarAngle = other.polarAngle;
	azimuthalAngle = other.azimuthalAngle;
}

SphericalCoordinate SphericalCoordinate::Normalize()
{
	return SphericalCoordinate(1, polarAngle, azimuthalAngle);
}

std::array<double, 3> CartesianCoordinate::toArray()
{
	return {x, y, z};
}

void CartesianCoordinate::operator=(const SphericalCoordinate& sphericalCoordinate) { 
	x = sphericalCoordinate.magnitude * sin(sphericalCoordinate.polarAngle) * cos(sphericalCoordinate.azimuthalAngle);
	y = sphericalCoordinate.magnitude * sin(sphericalCoordinate.polarAngle) * sin(sphericalCoordinate.azimuthalAngle);
	z = sphericalCoordinate.magnitude * cos(sphericalCoordinate.polarAngle);
}

void CartesianCoordinate::operator=(const CartesianCoordinate& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
}

void CartesianCoordinate::operator=(const std::array<double, 3>& other)
{
	x = other[0];
	y = other[1];
	z = other[2];
}

CartesianCoordinate CartesianCoordinate::Normalize()
{
	double mag = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	if (mag == 0)
		return *this;
	else
		return *this / mag;
}


Coordinate::Coordinate(double _x, double _y, double _z)
{
	cartesian = CartesianCoordinate(_x, _y, _z);
	spherical = cartesian;
}

Coordinate::Coordinate(std::array<double, 3> cartesianCoordinate)
{
	cartesian = CartesianCoordinate(cartesianCoordinate[0], cartesianCoordinate[1], cartesianCoordinate[2]);
	spherical = cartesian;
}

Coordinate::Coordinate(CartesianCoordinate coord)
{
	cartesian = coord;
	spherical = coord;
}

Coordinate::Coordinate(SphericalCoordinate coord)
{
	cartesian = coord;
	spherical = coord;
}


void Coordinate::operator=(const Coordinate& other)
{
	this->cartesian = other.cartesian;
	this->spherical = other.spherical;
}

void Coordinate::operator=(const std::array<double, 3>& other)
{
	this->cartesian = other;
	this->spherical = this->cartesian;
}

Coordinate Coordinate::operator+(const Coordinate& other)
{
	return Coordinate(this->GetX() + other.cartesian.x, this->GetY() + other.cartesian.y, this->GetZ() + other.cartesian.z);
}
Coordinate Coordinate::operator-(const Coordinate& other)
{
	return Coordinate(this->GetX() - other.cartesian.x, this->GetY() - other.cartesian.y, this->GetZ() - other.cartesian.z);
}
Coordinate Coordinate::operator*(const Coordinate& other)
{
	return Coordinate(this->GetX() * other.cartesian.x, this->GetY() * other.cartesian.y, this->GetZ() * other.cartesian.z);
}

Coordinate Coordinate::operator+(const double& number)
{
	return Coordinate(this->GetX() + number, this->GetY() + number, this->GetZ() + number);
}
Coordinate Coordinate::operator-(const double& number)
{
	return Coordinate(this->GetX() - number, this->GetY() - number, this->GetZ() - number);
}
Coordinate Coordinate::operator*(const double& number)
{
	return Coordinate(this->GetX() * number, this->GetY() * number, this->GetZ() * number);
}
Coordinate Coordinate::operator/(const double& number)
{
	return Coordinate(this->GetX() / number, this->GetY() / number, this->GetZ() / number);
}

Coordinate Coordinate::Normalize()
{
	return Coordinate(cartesian.Normalize());
}