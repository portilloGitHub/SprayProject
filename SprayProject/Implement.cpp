//===========================================================================
/// @file Implement.cpp
///
/// Implements class trimble::CImplement.
///
/// Copyright (c) 2017 Trimble, Inc.
//===========================================================================

#include "Implement.hpp"
namespace trimble
{


	//=============================================================================
	//=============================================================================
	//                             Implementation
	//=============================================================================
	//=============================================================================
	
	//-----------------------------------------------------------------------------
	// CImplement Constructor
	//-----------------------------------------------------------------------------
	CImplement::CImplement(double width, double distanceToTractor) :
		_Width(width),
		_DistanceToTractor(distanceToTractor),
		_currHeading(0.0),
		_isSpraying(false)
	{}


	//-----------------------------------------------------------------------------
	// CImplement::HandleNewTractorPosition(...)
	//-----------------------------------------------------------------------------
	void CImplement::HandleNewTractorPosition(const CEnuPosition& tractorPos,
		double heading)
	{
		//...
		UpdateAppliedArea(GenerateImplementPos(tractorPos, heading), heading);
		//...
	}


	//-----------------------------------------------------------------------------
	// CImplement::UpdateAppliedArea(...)
	//-----------------------------------------------------------------------------
	void CImplement::UpdateAppliedArea(const CEnuPosition& newImplementPos,
		double heading)
	{
		CEnuPosition newLPos = getLeftPos(_Width / 2);
		CEnuPosition newRPos = getRightPos(_Width / 2);
		CPolygon newPoly = GeneratePolygon(_currLPos,
			_currRPos,
			newLPos,
			newRPos);

		// Turn the nozzles off if the spray polygon overlaps where we've already
		// sprayed
		bool turnNozzlesOn = !_appliedArea.CheckOverlap(newPoly);

		if (_isSpraying)
		{
			// The spray we've got overlaps - turn off the nozzles
			_appliedArea.AddPolygon(newPoly);
		}

		SetAllNozzles(turnNozzlesOn);

		_isSpraying = turnNozzlesOn;
		_currPos = newImplementPos;
		_currHeading = heading;
		_currRPos = newRPos;
		_currLPos = newLPos;
	}

	// Member function: SetAllNozzles
	void CImplement::SetAllNozzles(bool val)
	{
		// Section turns on / off all nozzles.
		// This section should talk to the low level hardware in some manner
		// Example: 12 Nozzles are all on GPIO Port B & PORT B is a 16 bit register
		// ON => GPIO_PORTB = 0x0C
		// OFF => GPIO_PORTB = 0x00
	}
}

