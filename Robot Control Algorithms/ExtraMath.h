#pragma once
#include <cmath>
#include <array>
#include <vector>
#include <iostream>

#define PI (atan(1) * 4)

#define DEG_TO_RAD (PI / 180)
#define RAD_TO_DEG (180 / PI)

template<class T>
T clamp(T value, T min, T max) 
{
	if (value > max)
		value = max;
	if (value < min)
		value = min;

	return value;
}

template<class T>
std::array<T, 3> normalize(std::array<T, 3> vector, T scale)
{
	T magnitude = sqrt(pow(vector[0], 2) + pow(vector[1], 2) + pow(vector[2], 2));
	return { scale * vector[0] / magnitude, scale * vector[1] / magnitude, scale * vector[2] / magnitude };
}

template<class T>
std::array<T, 3> rotateX(std::array<T, 3> vector, T radians)
{
	std::array<T, 3> output;

	output[0] = vector[0];
	output[1] = cos(radians) * vector[1] - sin(radians) * vector[2];
	output[2] = sin(radians) * vector[1] + cos(radians) * vector[2];

	return output;
}

template<class T>
std::array<T, 3> rotateY(std::array<T, 3> vector, T radians)
{
	std::array<T, 3> output;

	output[0] = cos(radians) * vector[0] + sin(radians) * vector[2];
	output[1] = vector[1];
	output[2] = -sin(radians) * vector[0] + cos(radians) * vector[2];

	return output;
}

struct CartesianCoordinate;

struct SphericalCoordinate {
	double magnitude = 0, polarAngle = 0, azimuthalAngle = 0;
	std::array<double, 3> toArray();

	SphericalCoordinate() {};
	SphericalCoordinate(double _magnitude, double _polarAngle, double _azimuthalAngle) : magnitude(_magnitude), polarAngle(_polarAngle), azimuthalAngle(_azimuthalAngle) {};
	void operator=(const CartesianCoordinate&);
	void operator=(const SphericalCoordinate&);

	//SphericalCoordinate operator=(const SphericalCoordinate&) {};
	SphericalCoordinate operator+(const SphericalCoordinate& other) { return SphericalCoordinate(this->magnitude + other.magnitude, this->polarAngle + other.polarAngle, this->azimuthalAngle + other.azimuthalAngle); };
	SphericalCoordinate operator-(const SphericalCoordinate& other) { return SphericalCoordinate(this->magnitude - other.magnitude, this->polarAngle - other.polarAngle, this->azimuthalAngle - other.azimuthalAngle); };
	SphericalCoordinate operator*(const SphericalCoordinate& other) { return SphericalCoordinate(this->magnitude * other.magnitude, this->polarAngle * other.polarAngle, this->azimuthalAngle * other.azimuthalAngle); };
	/*
	SphericalCoordinate operator+(const double&) {};
	SphericalCoordinate operator-(const double&) {};
	SphericalCoordinate operator*(const double&) {};
	SphericalCoordinate operator/(const double&) {};
	*/

	SphericalCoordinate Normalize();
};

struct CartesianCoordinate {
	double x = 0, y = 0, z = 0;
	std::array<double, 3> toArray();

	CartesianCoordinate() {};
	CartesianCoordinate(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {};
	void operator=(const SphericalCoordinate&);
	void operator=(const CartesianCoordinate&);
	void operator=(const std::array<double, 3>&);

	CartesianCoordinate operator+(const CartesianCoordinate& other) { return CartesianCoordinate(x + other.x, y + other.y, z + other.z); };
	CartesianCoordinate operator-(const CartesianCoordinate& other) { return CartesianCoordinate(x - other.x, y - other.y, z - other.z); };
	CartesianCoordinate operator*(const CartesianCoordinate& other) { return CartesianCoordinate(x * other.x, y * other.y, z * other.z); };

	CartesianCoordinate operator+(const double& value) { return CartesianCoordinate(x + value, y + value, z + value); };
	CartesianCoordinate operator-(const double& value) { return CartesianCoordinate(x - value, y - value, z - value); };
	CartesianCoordinate operator*(const double& value) { return CartesianCoordinate(x * value, y * value, z * value); };
	CartesianCoordinate operator/(const double& value) { return CartesianCoordinate(x / value, y / value, z / value); };

	CartesianCoordinate Normalize();
};

struct Coordinate {
private:
	CartesianCoordinate cartesian;
	SphericalCoordinate spherical;

public:
	Coordinate() {};
	Coordinate(double _x, double _y, double _z);
	Coordinate(std::array<double, 3> cartesianCoordinate);
	//Coordinate(double _magnitude, double _polarAngle, double _azimuthalAngle);
	Coordinate(CartesianCoordinate);
	Coordinate(SphericalCoordinate);

	void SetX(double _x) { cartesian.x = _x; spherical = cartesian; };
	void SetY(double _y) { cartesian.y = _y; spherical = cartesian; };
	void SetZ(double _z) { cartesian.z = _z; spherical = cartesian; };

	double GetX() { return cartesian.x; };
	double GetY() { return cartesian.y; };
	double GetZ() { return cartesian.z; };

	void SetMagnitude(double _magnitude) { spherical.magnitude = _magnitude; cartesian = spherical; };
	void SetPolarAngle(double _polarAngle) { spherical.polarAngle = _polarAngle; cartesian = spherical; };
	void SetAzimuthalAngle(double _azimuthalAngle) { spherical.azimuthalAngle = _azimuthalAngle; cartesian = spherical; };

	double GetMagnitude() { return spherical.magnitude; };
	double GetPolarAngle() { return spherical.polarAngle; };
	double GetAzimuthalAngle() { return spherical.azimuthalAngle; };


	void operator=(const Coordinate&);
	void operator=(const std::array<double, 3>&);

	Coordinate operator+(const Coordinate&);
	Coordinate operator-(const Coordinate&);
	Coordinate operator*(const Coordinate&);

	Coordinate operator+(const double&);
	Coordinate operator-(const double&);
	Coordinate operator*(const double&);
	Coordinate operator/(const double&);

	Coordinate Normalize();

	Coordinate RotateX();
};


