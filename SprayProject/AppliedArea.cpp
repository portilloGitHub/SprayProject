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
	// May need to add some initialization logic here. 
	// Keep empty for now.
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
		// (1) Check to see if any of the nozzles lie inside a sprayed area
		int nozzelControlValue = testSprayedArea(vectorOfNozzles);
	}


	int CAppliedArea::testSprayedArea(const std::vector<CEnuPosition> vectorOfNozzless)
	{
		int nozzelControl = 0;
		std::vector<bool> nozzelState;

		// (1) Test each nozzel to make sure it is not in an already sprayed area
		for (int i = 0; i < vectorOfNozzless.size(); i++)
		{
			if (isOnBorder(vectorOfNozzless[i]))
			{
				nozzelState.push_back(true);
			}
			else if (isInsidePolygon(vectorOfNozzless[i]))
			{
				nozzelState.push_back(true);
			}
			else nozzelState.push_back(false);
		}

		// (2) Evaluate the nozzleState vector and create a singular int hex vaue 
		//		that will be used to send to the control register 
		// Assume: 16 bit register
		// Bit shift and OR it with the last value as we itterate through the vector
		for(int j = 0; j < nozzelState.size(); j++)
		{
			if (nozzelState[j] == false)
			{
				nozzelControl |= (0 << j);
			}
			else if (nozzelState[j] == true)
			{
				nozzelControl |= (1 << j);
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