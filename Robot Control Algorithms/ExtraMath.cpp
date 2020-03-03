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
		polarAngle = atan2(sqrt(pow(cartesianCoordinate.x, 2) + pow(cartesianCoordinate.y, 2)), cartesianCoordinate.z);
		azimuthalAngle = atan2(cartesianCoordinate.y, cartesianCoordinate.x);
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


SphericalCoordinate Coordinate::GetSpherical()
{
	return spherical;
}

CartesianCoordinate Coordinate::GetCartesian()
{
	return cartesian;
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

Coordinate Coordinate::RotateX(double radians)
{
	Coordinate output;

	output.SetX(cartesian.x);
	output.SetY(cos(radians) * cartesian.y - sin(radians) * cartesian.z);
	output.SetZ(sin(radians) * cartesian.y + cos(radians) * cartesian.z);

	return output;
}

Coordinate Coordinate::RotateY(double radians)
{
	Coordinate output;

	output.SetX(cos(radians) * cartesian.x + sin(radians) * cartesian.z);
	output.SetY(cartesian.y);
	output.SetZ(-sin(radians) * cartesian.x + cos(radians) * cartesian.z);

	return output;
}

Coordinate Coordinate::RotateZ(double radians)
{
	Coordinate output;

	output.SetX(cos(radians) * cartesian.x - sin(radians) * cartesian.y);
	output.SetY(sin(radians) * cartesian.x + cos(radians) * cartesian.y);
	output.SetZ(cartesian.z);

	return output;
}

Coordinate Coordinate::RotateXZPlane(double radians)
{
	Coordinate output;

	output.SetX(cos(radians) * cartesian.x - sin(radians) * cartesian.z);
	output.SetY(cartesian.y);
	output.SetZ(sin(radians) * cartesian.x + cos(radians) * cartesian.z);

	return output;
}

Coordinate Coordinate::ToLocalCartesian(Coordinate other)
{
	return other - this->cartesian;
}

Coordinate Coordinate::ToLocalSpherical(Coordinate other)
{
	return other.RotateZ(-GetAzimuthalAngle()).RotateY(-GetPolarAngle());
}
