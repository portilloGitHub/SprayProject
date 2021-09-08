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
				// Only offest the very first _oldLeft & _newLeft data points.
				// We are calibrating the spray area at this point and using that as our polygon area
				// The other points will be processed by offsetENUPoints
				// ASSUME: Heading in {0,90,180,270} in clockwise rotation
				if (_Heading == 0)
				{
					_oldLeft.setEast = _oldLeft.getEast - ((_Width / _numNozzles) / 2);
					_newLeft.setEast = _newLeft.getEast - ((_Width / _numNozzles) / 2);
				}
				else if (_Heading == 90)
				{
					_oldLeft.setNorth = _oldLeft.getNorth + ((_Width / _numNozzles) / 2);
					_newLeft.setNorth = _newLeft.getNorth + ((_Width / _numNozzles) / 2);
				}
				if (_Heading == 180)
				{
					_oldLeft.setEast = _oldLeft.getEast + ((_Width / _numNozzles) / 2);
					_newLeft.setEast = _newLeft.getEast + ((_Width / _numNozzles) / 2);
				}
				else if (_Heading == 270)
				{
					_oldLeft.setNorth = _oldLeft.getNorth - ((_Width / _numNozzles) / 2);
					_newLeft.setNorth = _newLeft.getNorth - ((_Width / _numNozzles) / 2);
				}

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
	CEnuPosition CPolygon::offsetENUPoints(CEnuPosition& enuData)
	{
		// Example: 120" / 12" = 10" spacing
		double spacingDistnace = (_Width / _numNozzles); 

		if (_Heading == 0)
		{
			// Positive North
			enuData.setEast = enuData.getEast + spacingDistnace;
			enuData.setNorth = enuData.getNorth;
		}
		else if (_Heading == 90)
		{
			// Positive East
			enuData.setEast = enuData.getEast;
			enuData.setNorth = enuData.getNorth - spacingDistnace;
		}
		else if (_Heading == 180)
		{
			// Negative North
			enuData.setEast = enuData.getEast - spacingDistnace;
			enuData.setNorth = enuData.getNorth;
		}
		else if (_Heading == 270)
		{
			// Negative East
			enuData.setEast = enuData.getEast;
			enuData.setNorth = enuData.getNorth + spacingDistnace;
		}

		enuData.setUp = enuData.getUp;
	}
}

