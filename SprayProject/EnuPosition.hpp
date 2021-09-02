//============================================================================
/// @file EnuPosition.hpp
///
/// Declares class trimble::CEnuPosition.
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

		double East() const { return _east; }
		double North() const { return _north; }
		double Up() const { return _up; }

		double& operator[](unsigned int i)
		{
			switch (i)
			{
			case 0: return _east; break;
			case 1: return _north; break;
			case 2: return _up; break;
			}
		}

		void FromLLA(const CLlaPos& llaPos);
		void FromXYZ(const CXyzPos& xyzPos);

		double _east;
		double _north;
		double _up;
	};


}
#endif

