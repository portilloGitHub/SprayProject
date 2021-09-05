#include "Polygon.hpp"

namespace trimble
{
	CPolygon::CPolygon()
	{
	}

	CPolygon CPolygon::getArea()
	{
		double deltaLeftEast = 0.0, deltaRightEast = 0.0;
		double deltaLeftNorth = 0.0, deltaRightNorth = 0.0;

		deltaLeftEast = (_newLeft.getEast - _oldLeft.getEast);
		deltaRightEast = (_newRight.getEast - _newRight.getEast);
		deltaLeftNorth = (_newLeft.getNorth - _oldLeft.getNorth);
		deltaRightNorth = (_newRight.getNorth - _oldRight.getNorth);

		// Check to make sure vehcile has moved
		if(	deltaLeftEast != 0 && 
			deltaLeftNorth != 0 &&
			deltaRightEast != 0 &&
			deltaRightNorth != 0 )
		{
			// Assumption: Nozzles are always evenly spaced out. 
			// (1) Calculate the width of the boom based on ENU & heading
			// (2) Calculate the spacing of the nozzels based on the updated 
			//		ENU and heading calculation from step 1
			// (3) Return the 4 ENU points for each of the nozzels
			//
			// 
		}
	}
}

