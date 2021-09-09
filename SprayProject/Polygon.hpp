//============================================================================
/// @file Polgon.hpp
///
/// Declares class trimble::CPolygon.
/// Description:
///		Creates polygons for each nozzel. It is assumed that each nozzle is
///		evenly spaced out.
///
/// Copyright (c) 2021 Trimble, Inc.
//============================================================================
#ifndef _POLYGON_HPP_
#define _POLYGON_HPP_

#include "EnuPosition.hpp"

namespace trimble
{

	//-----------------------------------------------------------------------------
	// Class
	//-----------------------------------------------------------------------------
	class CPolygon
	{

	public:
		CPolygon() : _numNozzles(0), _Width(0.0), _Heading(0.0), _nozzleNumber(0) {};

		CPolygon(const CEnuPosition& oldLeft,
			const CEnuPosition& oldRight,
			const CEnuPosition& newLeft,
			const CEnuPosition& newRight,
			const double width,
			const int numNozzles,
			const double heading,
			const int nozzleNumber) :
			_oldLeft(oldLeft),
			_oldRight(oldRight),
			_newLeft(newLeft),
			_newRight(newRight),
			_Width(width),
			_numNozzles(numNozzles),
			_Heading(heading),
			_nozzleNumber(nozzleNumber) {};

		// Vector that holds CEnuPostion for polygon data
		// {oldLeft, newLeft, newRight, oldRight}
		std::vector<CEnuPosition> polygonVector;
		CPolygon getPolygonVector();

		

	private:
		CEnuPosition _oldLeft;
		CEnuPosition _oldRight;
		CEnuPosition _newLeft;
		CEnuPosition _newRight;
		const int _numNozzles,_nozzleNumber;
		const double _Width,_Heading;
	};
}

#endif
