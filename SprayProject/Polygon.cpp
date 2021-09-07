#include <vector>
#include "EnuPosition.hpp"
#include "Polygon.hpp"

namespace trimble
{
	CPolygon CPolygon::getPolygonVector()
	{
		std::vector<CEnuPosition> temp;

		// ASSUME: Linear heading at 0,90,180,270 degrees
		//			N - 0.0
		//			E - 90.0
		//			S - 180.0
		//			W - 270
		// REASON: Keep math simple to calculate correct spacing for each valve
		// TODO: Account for non-linear heading with translation and rotation logic

		for (int i = 0; i < (_numNozzles - 1); i++)
		{
			// Establish "home" that all nozzels will be offset from
			// Selected the furthest left side of the Boom as the vheicle is facing North
			// Logic follows a clockwise rotation starting from oldLeft
			// oldLeft -> newLeft -> newRight -> oldRight
			// vector holds info {oldLeft,newLeft,newRight,oldRight}
			if (i == 0)
			{
				// Home polygon
				temp.push_back(_oldLeft);
				temp.push_back(_newLeft);
				temp.push_back(offsetENUPoints(_newLeft)); // Becomes the next new left
				temp.push_back(offsetENUPoints(_oldLeft)); // Becomes the next old left
			}
			else
			{
				// Next nozzle polygon
				CEnuPosition _tempOldLeft = vectorOfNozzels[i - 1][3];
				CEnuPosition _tempNewLeft = vectorOfNozzels[i - 1][2];
				temp.push_back(_tempOldLeft);					// previous oldLeft
				temp.push_back(_tempNewLeft);					// previous newLeft
				temp.push_back(offsetENUPoints(_tempNewLeft));	// next newLeft
				temp.push_back(offsetENUPoints(_tempOldLeft));	// next oldLeft
			}

			vectorOfNozzels.push_back(temp);
		}
	}

	// Performes offset calcuations for each nozzel based on heading 
	CEnuPosition CPolygon::offsetENUPoints(const CEnuPosition& enuData)
	{
		double east, north, up;
		double spacingDistnace = (_Width / _numNozzles);

		if (_Heading == 0)
		{
			// Positive North
			east = enuData.getEast + spacingDistnace;
			north = enuData.getNorth;
			up = enuData.getUp;
		}
		else if (_Heading == 90)
		{
			// Positive East
			east = enuData.getEast;
			north = enuData.getNorth - spacingDistnace;
			up = enuData.getUp;
		}
		else if (_Heading == 180)
		{
			// Negative North
			east = enuData.getEast - spacingDistnace;
			north = enuData.getNorth;
			up = enuData.getUp;
		}
		else if (_Heading == 270)
		{
			// Negative East
			east = enuData.getEast;
			north = enuData.getNorth + spacingDistnace;
			up = enuData.getUp;
		}

		CEnuPosition correctedENUPoints = CEnuPosition(east, north, up);
	}
}

