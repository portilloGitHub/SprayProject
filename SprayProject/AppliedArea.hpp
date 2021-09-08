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
		
		// Serach throught the vector list and compare if current ENU position 
		// matches any vector ENU postions
		// TODO: R&D on better methods to iterate and compare vector data
		//			Search logic should be added in ApplieArea.cpp
		int CheckOverlap(const CPolygon& poly);


	private:
		// TODO not sure if this is the proper container
		std::vector<CPolygon> CPolygonVector;
		std::vector<CEnuPosition> enuCentroidVector;
		//CPolygonVector _polygons;

		void findCentroidOfPolygon(const CPolygon& poly);

		int testCentroid(const CPolygon& poly);

		bool isOnBorder(const CPolygon& poly);

		bool isInsidePolygon(const CPolygon& poly);
		
	};


}
#endif

