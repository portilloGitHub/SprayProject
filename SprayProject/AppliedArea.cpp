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
	int CAppliedArea::CheckOverlap(const CPolygon& poly)
	{
		// (1) Calculate the centroid for each polygon on the boom
		findCentroidOfPolygon(poly);

		// (2) Check to see if centroid lies on any of the borders or inside the polygon
		int nozzelControlValue = testCentroid(poly);

		// (3) return nozzelControlValue
		return nozzelControlValue;
	}

	void CAppliedArea::findCentroidOfPolygon(const CPolygon& poly)
	{
		double x0 = 0.0, x1 = 0.0;
		double y0 = 0.0, y1 = 0.0;
		double centroidX = 0.0, centroidY = 0.0;
		double A = 0.0, signedArea; // Shoelace formula
		std::vector<CEnuPosition> centroidValues;

		// Find the centroid of the polygon
		// Use the centroid to test if it is in any other pre existing polygon
		// CLOCKWISE
		for (int i=0;i < poly.vectorOfNozzels.size();i++)
		{
			// Since we are dealing with rectangles, its OK to hard code this. 
			// Change this later if desried.
			for (int j = 0; j < 4; j++)
			{
				
				x0 = poly.vectorOfNozzels[i][j].getEast();
				y0 = poly.vectorOfNozzels[i][j].getNorth();
				x1 = poly.vectorOfNozzels[i][(j + 1) % 4].getEast();
				y1 = poly.vectorOfNozzels[i][(j + 1) % 4].getNorth();
				

				// Calculate value of A using shoelace formula
				A = ((x0 * y1) - (x1 * y0));
				signedArea += A;

				// Calculate the coordinates of centroid of the polygon
				centroidX += ((x0 + x1) * A);
				centroidY += ((y0 + y1) * A);
			}

			signedArea *= 0.5;
			centroidX = centroidX / (6 * signedArea);
			centroidY = centroidY / (6 * signedArea);
			
			// I dont care for up since it is not critical for this right now
			CEnuPosition centroid = CEnuPosition(centroidX,centroidY,poly.vectorOfNozzels[0][0].getUp);
			enuCentroidVector.push_back(centroid);
		}
	}

	int CAppliedArea::testCentroid(const CPolygon& poly)
	{
		int nozzelControl = 0;

		// (1) Test centroid with respect to otehr polygons
		std::vector<bool> nozzelState;
		for (int i = 0; i < poly.vectorOfNozzels.size(); i++)
		{
			if (isOnBorder(poly))
			{
				nozzelState.push_back(true);
			}
			else if (isInsidePolygon(poly))
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

		return nozzelControl;
	}

	bool CAppliedArea::isOnBorder(const CPolygon& poly) 
	{
		// TODO: Add logic here to test if any of the current polygon points
		//			lie on any of the previous polygon border lines
		// return true; // if the point lies on the border 
		// return false; // if the point lies on the border 
	}

	bool CAppliedArea::isInsidePolygon(const CPolygon& poly)
	{
		// TODO: Add logic here to test if any of the current polygon points
		//			lie on any of the previous polygon border lines
		// return true; // if the point lies on the border 
		// return false; // if the point lies on the border 
	}
}