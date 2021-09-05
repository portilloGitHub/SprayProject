//===========================================================================
/// @file AppliedArea.cpp
///
/// Implements class trimble::CAppliedArea.
///
/// Copyright (c) 2017 Trimble, Inc.
//===========================================================================

#include "AppliedArea.hpp"

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
	// Push the latest polygon to the vector list
	//-----------------------------------------------------------------------------
	bool CAppliedArea::CheckOverlap(const CPolygon& poly) const
	{
		if (std::find(CPolygonVector.begin(),CPolygonVector.end(),poly) != CPolygonVector.end())
		{
			return true;
		} 
		return false;
	}
}