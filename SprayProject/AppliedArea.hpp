//============================================================================
/// @file AppliedArea.hpp
///
/// Declares class trimble::CAppliedArea.
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
		bool CheckOverlap(const CPolygon& poly) const;

	private:
		// TODO not sure if this is the proper container
		std::vector<CPolygon> CPolygonVector;
		CPolygonVector _polygons;
	};


}
#endif

