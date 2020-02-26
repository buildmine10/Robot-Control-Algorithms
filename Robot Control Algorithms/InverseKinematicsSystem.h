#pragma once

#include <cstdarg>
#include <cmath>
#include <array>
#include <vector>
#include <functional>
#include <iostream>

#include "ExtraMath.h"

class InverseKinematicsSystem
{
public: 
	struct Segment;

	void update();
	void setTarget(std::array<double, 3> target);

private:
	std::vector<Segment> m_segments;

	std::array<double, 3> m_targetPosition;
	std::array<double, 3> m_rootPosition;
	std::array<double, 2> m_rootAngle;

	void forwardKinematicUpdate();
	void updateLocalAngles();

public:
	InverseKinematicsSystem(std::array<double, 3> rootPosition, std::array<double, 2> rootAngle, int numberOfSections, ...);
	std::vector<Coordinate> points;

	static struct Segment
	{
		friend class InverseKinematicsSystem;
		Segment() = delete;
		//requires the length of the segment
		Segment(
			double _length,

			std::array<double, 2> _xAngleRange = { -180.0 * DEG_TO_RAD, 180.0 * DEG_TO_RAD },
			std::array<double, 2> _yAngleRange = { -180.0 * DEG_TO_RAD, 180.0 * DEG_TO_RAD },
			std::array<double, 2> _angleOffset = { 0, 0 },

			std::array<double, 2> _xLinearRange = { 0, 0 },
			std::array<double, 2> _yLinearRange = { 0, 0 }

		):	length(_length),

			xAngleRange(_xAngleRange),
			yAngleRange(_yAngleRange),
			angleOffset(_angleOffset),

			xLinearRange(_xLinearRange),
			yLinearRange(_yLinearRange)
		{};

		Coordinate getStartPosition();
		Coordinate getEndPosition();
		std::array<double, 2> getAngleOffset();
		std::array<double, 2> getLinearMovement();
		std::array<double, 2> getWorldAngle();

		void inverseKinematicUpdate(Coordinate targetPosition);
		void inverseKinematicUpdate(std::array<double, 3> targetPosition);
		
	private:
		double length;//units: user defined

		//z is not used because only two angle are need to represent direction in 3D space
		std::array<double, 2> xAngleRange;//[0]: min, [1]: max
		std::array<double, 2> yAngleRange;//units: radians

		//z is not used because that would require physical separation
		std::array<double, 2> xLinearRange;//[0]: min, [1]: max
		std::array<double, 2> yLinearRange;//units: user defined

		Coordinate startPosition;
		Coordinate endPosition;

		std::array<double, 2> linearMovement = { 0, 0 };//x, y relative to segment. The segment arm comes off of this
		Coordinate segmentArm;//The direction and length of segment arms (world space)

		std::array<double, 2> angleOffset;//the change in angle between the parent segment's world angle and the world angle of the fixture that the segment is attached to

	};
	////////////////////////////
	//end of Segment declaration
	////////////////////////////
};
