// Robot Control Algorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//make an output file
//test in unity

#include <iostream>
#include <fstream>
#include <string>
#include "ExtraMath.h"

#include "InverseKinematicsSystem.h"

void setTarget(double x, double y, double z);
void print();

InverseKinematicsSystem inverseKinematicsSystem({ 0, 0, 0 }, { 0, 0 }, 1, InverseKinematicsSystem::Segment(1.0, { -45 * DEG_TO_RAD, 45 * DEG_TO_RAD }, { -45 * DEG_TO_RAD, 45 * DEG_TO_RAD }));// , InverseKinematicsSystem::Segment(1.0), InverseKinematicsSystem::Segment(1.0));
std::ofstream OFile{"InterfaceFile.txt"};
std::ifstream IFile{ "InterfaceFile.txt" };

int main()
{
	print();
	setTarget(1, 1, 1);
	inverseKinematicsSystem.update();
	inverseKinematicsSystem.update();
	while (true) {

	}
}

void setTarget(double x, double y, double z) {
	inverseKinematicsSystem.setTarget({ x, y, z });
}

void print() {
	std::string output;
	for (Coordinate point : inverseKinematicsSystem.points)
	{
		output.append(std::to_string(point.GetX()));
		output.append(",");
		output.append(std::to_string(point.GetY()));
		output.append(",");
		output.append(std::to_string(point.GetZ()));
		output.append("\n");
	}
	
	OFile << output;
	OFile.close();
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
