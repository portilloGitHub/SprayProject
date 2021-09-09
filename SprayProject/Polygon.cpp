#include <vector>
#include "EnuPosition.hpp"
#include "Polygon.hpp"

namespace trimble
{
	CPolygon CPolygon::getPolygonVector()
	{
		int spacingConstant = ((_Width / _numNozzles) * _nozzleNumber);
		int sprayCoverage = (_Width / _numNozzles) / 2;

		// ASSUME: Linear heading at 0,90,180,270 degrees
		//			N - 0.0
		//			E - 90.0
		//			S - 180.0
		//			W - 270
		// REASON: Keep math simple to calculate correct spacing for each valve
		// TODO: Account for non-linear heading with translation and rotation logic

		// Selected the furthest left side of the Boom as the vheicle is facing North
		// Logic follows a clockwise rotation starting from oldLeft
		// oldLeft -> newLeft -> newRight -> oldRight
		// vector holds info {oldLeft,newLeft,newRight,oldRight}

		// The other points will be processed by offset calculations from the left most valve
		// ASSUME: Heading in {0,90,180,270} in clockwise rotation

		// Spray Angle: Accounting for spray angle width. 
		// ASSUME: Spray angle is 10 degress and valve is the mid point 
		//			Adding +/- 5 degrees from the calculated spray valve
		if (_Heading == 0)
		{
			// Establish polygon based on left most sprayCovearge
			_oldLeft.setEast = (_oldLeft.getEast - sprayCoverage) + spacingConstant;
			_newLeft.setEast = (_newLeft.getEast - sprayCoverage) + spacingConstant;
			_newRight.setEast = (_newLeft.getEast + (sprayCoverage * 2)) + spacingConstant;
			_oldRight.setEast = (_oldLeft.getEast + (sprayCoverage * 2)) + spacingConstant;
		}
		else if (_Heading == 90)
		{
			_oldLeft.setNorth = (_oldLeft.getNorth + sprayCoverage) - spacingConstant;
			_newLeft.setNorth = (_newLeft.getNorth + sprayCoverage) - spacingConstant;
			_newRight.setNorth = (_newLeft.getNorth - (sprayCoverage * 2)) - spacingConstant;
			_oldRight.setNorth = (_oldLeft.getNorth - (sprayCoverage * 2)) - spacingConstant;
		}
		if (_Heading == 180)
		{
			_oldLeft.setEast = (_oldLeft.getEast + sprayCoverage) - spacingConstant;
			_newLeft.setEast = (_newLeft.getEast + sprayCoverage) - spacingConstant;
			_newRight.setEast = (_newLeft.getEast - (sprayCoverage * 2)) - spacingConstant;
			_oldRight.setEast = (_oldLeft.getEast - (sprayCoverage * 2)) - spacingConstant;
		}
		else if (_Heading == 270)
		{
			_oldLeft.setNorth = (_oldLeft.getNorth - sprayCoverage) + spacingConstant;
			_newLeft.setNorth = (_newLeft.getNorth - sprayCoverage) + spacingConstant;
			_newRight.setNorth = (_newLeft.getNorth + (sprayCoverage * 2)) + spacingConstant;
			_oldRight.setNorth = (_oldLeft.getNorth + (sprayCoverage * 2)) + spacingConstant;
		}


		polygonVector.push_back(_oldLeft);
		polygonVector.push_back(_newLeft);
		polygonVector.push_back(_newRight);
		polygonVector.push_back(_oldRight);
	}
}