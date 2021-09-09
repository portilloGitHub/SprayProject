//===========================================================================
/// @file AppliedArea.cpp
///
/// Implements class trimble::CAppliedArea.
///
/// Copyright (c) 2017 Trimble, Inc.
//===========================================================================

#include "AppliedArea.hpp"
#include "Implement.hpp"

namespace trimble
{
	//-----------------------------------------------------------------------------
	// Constructor
	//----------------------------------------------------------------------------- 
	CAppliedArea::CAppliedArea()
	{
	}

	//-----------------------------------------------------------------------------
	// CAppliedArea::AddPolygon (...)
	// Push the latest polygon to the vector list
	//-----------------------------------------------------------------------------
	void CAppliedArea::AddPolygon (const CPolygon& poly)
	{
		CPolygonVector.push_back(poly);
	}

	//-----------------------------------------------------------------------------
	// CAppliedArea::CheckOverlap (...)
	//-----------------------------------------------------------------------------
	void CAppliedArea::CheckOverlap(const std::vector<CEnuPosition> vectorOfNozzles)
	{
		// Create a singular int hex value that will be used to send to the control register 
		// Assume: 16 bit register
		// Bit shift and OR it with the last value
		// 
		// Valve 0 (left most valve) is little endian 

		nozzleControl = 0x0000; // Set the nozzle control to default 0x0000

		// Test each nozzel to make sure it is not in an already sprayed area
		for (int i = 0; i < vectorOfNozzles.size(); i++)
		{
			if (isOnBorder(vectorOfNozzles[i]) || 
				isInsidePolygon(vectorOfNozzles[i]))
			{
				// Turn OFF nozzle. On Border or its located inside and existing polygon
				nozzleControl |= (0 << i);
			}
			else
			{
				// Turn ON nozzle. Area has not been sprayed yet.
				nozzleControl |= (1 << i);
			}
		}
	}

	bool CAppliedArea::isOnBorder(const CEnuPosition vectorOfNozzless_element)
	{
		// TODO: Add logic here to test if any of the current polygon points
		//			lie on any of the previous polygon border lines
		// return true; // if the point lies on the border 
		// return false; // if the point lies on the border 
	}

	bool CAppliedArea::isInsidePolygon(const CEnuPosition vectorOfNozzles_element)
	{
		// TODO: Add logic here to test if any of the current polygon points
		//			lie on any of the previous polygon border lines
		// return true; // if the point lies on the border 
		// return false; // if the point lies on the border 
	}
}