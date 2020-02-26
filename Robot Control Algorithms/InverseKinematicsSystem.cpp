#include "InverseKinematicsSystem.h"



InverseKinematicsSystem::InverseKinematicsSystem(std::array<double, 3> rootPosition, std::array<double, 2> rootAngle, int numberOfSections, ...)
{
	m_rootPosition[0] = rootPosition[0] * DEG_TO_RAD;
	m_rootPosition[1] = rootPosition[1] * DEG_TO_RAD;
	m_rootPosition[2] = rootPosition[2] * DEG_TO_RAD;

	m_rootAngle[0] = rootPosition[0] * DEG_TO_RAD;
	m_rootAngle[1] = rootPosition[1] * DEG_TO_RAD;

	std::vector<Segment*> temp;
	points.push_back(m_rootPosition);

	va_list segments;
	va_start(segments, numberOfSections);
	
	//adds the segments to the system
	for (int i = 0; i < numberOfSections; ++i) 
	{
		temp.push_back(&va_arg(segments, Segment));//Ignore the intellisense error on the period. No error actually exists.
		
		
		m_segments.push_back(*temp[i]);
		m_segments[i].segmentArm.SetZ(1);
		points.push_back(m_segments[i].endPosition);
		//sets the parent
		if (i == 0) 
		{
			m_segments[i].angleOffset = m_rootAngle;
		}
	}

	va_end(segments);

	forwardKinematicUpdate();
}

void InverseKinematicsSystem::update()
{
	for (int i = m_segments.size() - 1; i >= 0; i--) 
	{	
		if (i == m_segments.size() - 1) 
		{
			m_segments[i].inverseKinematicUpdate(m_targetPosition);
		}
		else 
		{
			m_segments[i].inverseKinematicUpdate(m_segments[i + 1].startPosition);
		}
	}

	forwardKinematicUpdate();

	std::cout << std::endl << "( " << m_segments[m_segments.size() - 1].endPosition.GetX() << ", " << m_segments[m_segments.size() - 1].endPosition.GetY() << ", " << m_segments[m_segments.size() - 1].endPosition.GetZ() << " )" << std::endl;

	std::cout << std::endl;
}

void InverseKinematicsSystem::setTarget(std::array<double, 3> target)
{
	m_targetPosition = target;
}

void InverseKinematicsSystem::forwardKinematicUpdate()
{
	for (int i = 0; i < m_segments.size(); ++i)
	{
		//std::cout << "segment arm( " << m_segments[i].segmentArm.GetX() << ", " << m_segments[i].segmentArm.GetY() << ", " << m_segments[i].segmentArm.GetZ() << " )" << std::endl;
		std::cout << i << " ( " << m_segments[i].endPosition.GetX() << ", " << m_segments[i].endPosition.GetY() << ", " << m_segments[i].endPosition.GetZ() << " )" << std::endl;

		if (i > 0)
		{
			//std::cout << i << " Parent ( " << m_segments[i - 1].endPosition.GetX() << ", " << m_segments[i - 1].endPosition.GetY() << ", " << m_segments[i - 1].endPosition.GetZ() << " )" << std::endl;
			m_segments[i].startPosition = m_segments[i - 1].endPosition;
			m_segments[i].endPosition = m_segments[i].startPosition + m_segments[i].segmentArm;
		}
		else
		{
			m_segments[i].startPosition = m_rootPosition;
			m_segments[i].endPosition = m_segments[i].startPosition + m_segments[i].segmentArm;
		}

		//std::cout << i << " ( " << m_segments[i].endPosition.GetX() << ", " << m_segments[i].endPosition.GetY() << ", " << m_segments[i].endPosition.GetZ() << " )" << std::endl << std::endl;
	}
	
	std::cout << "( " << m_segments[m_segments.size() - 1].endPosition.GetX() << ", " << m_segments[m_segments.size() - 1].endPosition.GetY() << ", " << m_segments[m_segments.size() - 1].endPosition.GetZ() << " )" << std::endl << std::endl;
}


Coordinate InverseKinematicsSystem::Segment::getStartPosition()
{
	return startPosition;
}

Coordinate InverseKinematicsSystem::Segment::getEndPosition()
{
	return endPosition;
}

std::array<double, 2> InverseKinematicsSystem::Segment::getAngleOffset()
{
	return angleOffset;
}

std::array<double, 2> InverseKinematicsSystem::Segment::getLinearMovement()
{
	return linearMovement;
}

void InverseKinematicsSystem::Segment::inverseKinematicUpdate(Coordinate targetPosition)
{
	//world space is relative to the world
	//local space is relative to the segment (the origin is centered on the start point, the positive z direction is in the direction of the parent segement's world angle plus the segment's angle offset)
	endPosition = targetPosition;

	segmentArm = endPosition - startPosition;
	segmentArm = segmentArm.Normalize();
	if (segmentArm.GetX() == 0 && segmentArm.GetY() == 0 && segmentArm.GetZ() == 0)
		segmentArm.SetX(1);
	segmentArm = segmentArm * length;

	startPosition = endPosition - segmentArm;

	//std::cout << "target position ( " << targetPosition.GetX() << ", " << targetPosition.GetY() << ", " << targetPosition.GetZ() << " )" << std::endl;
	//std::cout << "segment arm ( " << segmentArm.GetX() << ", " << segmentArm.GetY() << ", " << segmentArm.GetZ() << " )" << std::endl;
}

void InverseKinematicsSystem::Segment::inverseKinematicUpdate(std::array<double, 3> targetPosition)
{
	inverseKinematicUpdate(Coordinate(targetPosition));
}

