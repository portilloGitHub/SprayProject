//============================================================================
/// @file EnuPosition.hpp
///
/// Declares class trimble::CEnuPosition.
///
/// Description: Class to process geospatial data to usable data for 
///		points on the tractor and implement
///
/// Copyright (c) 2017 Trimble, Inc.
//============================================================================
#ifndef _ENUPOSITION_HPP_
#define _ENUPOSITION_HPP_

namespace trimble
{


	//-----------------------------------------------------------------------------
	// Class
	//-----------------------------------------------------------------------------
	class CEnuPosition
	{
	public:
		CEnuPosition() : _east(0.0), _north(0.0), _up(0.0) {}

		CEnuPosition(double east, double north, double up) :
			_east(east), _north(north), _up(up) {}

		// Added "get" to make this easier to understand
		double getEast() const { return _east; }
		double getNorth() const { return _north; }
		double getUp() const { return _up; }


		double& operator[](unsigned int i)
		{
			switch (i)
			{
			case 0: return _east; break;
			case 1: return _north; break;
			case 2: return _up; break;
			}
		}

		// Create classes for CLlaPos & CXyzPos
		// These should calculate and mamange the distance from home origin
		// TODO: DOCUMENT THIS SECTION with workflows and theory 
		// TODO: Get this done via psudeo code
		void FromLLA(const CLlaPos& llaPos); // Geodetic (Lat,Long,meter)
		void FromXYZ(const CXyzPos& xyzPos); // ENU (meter,meter,meter)
		// End section

	private:

		double _east;
		double _north;
		double _up;
	};


}
#endif

