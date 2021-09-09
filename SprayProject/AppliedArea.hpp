//============================================================================
/// @file AppliedArea.hpp
///
/// Declares class trimble::CAppliedArea.
///
/// Description:  Class to manage polygons based on overlapping areas
///
/// Copyright (c) 2017 Trimble, Inc.
//============================================================================
#ifndef _APPLIEDAREA_HPP_
#define _APPLIEDAREA_HPP_

#include <vector>
#include "Polygon.hpp"

namespace trimble
{


	//-----------------------------------------------------------------------------
	// Class
	//-----------------------------------------------------------------------------
	class CAppliedArea
	{
	public:
		CAppliedArea();

		// Add new polygon info to the vector list
		void AddPolygon(const CPolygon& poly);			
		
		// Compare the current vectorOfNozzles ENU location to established polygons
		// TODO: R&D on better methods to iterate and compare vector data
		//			Search logic should be added in ApplieArea.cpp
		void CheckOverlap(const std::vector<CEnuPosition> vectorOfNozzles);

		int getAreaControlValue() { return nozzleControl; }


	private:
		// Vector of Polygons
		std::vector<CPolygon> CPolygonVector;

		int nozzleControl;

		bool isOnBorder(const CEnuPosition vectorOfNozzless_element);

		bool isInsidePolygon(const CEnuPosition vectorOfNozzless_element);
		
	};


}
#endif

