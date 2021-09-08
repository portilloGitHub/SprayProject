//===========================================================================
/// @file Implement.cpp
///
/// Implements class trimble::CImplement.
///
///	Description: CPP source file that adds functionality to the
///		methods defined in Implement.hpp
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
	CImplement::CImplement(double width, double distanceToTractor,int numNozzles) :
		_Width(width),
		_DistanceToTractor(distanceToTractor),
		_currHeading(0.0),
		_isSpraying(false),
		_numNozzles(numNozzles)
	{}


	//-----------------------------------------------------------------------------
	// CImplement::HandleNewTractorPosition(...)
	//-----------------------------------------------------------------------------
	void CImplement::HandleNewTractorPosition(const CEnuPosition& tractorPos,
		double heading)
	{
		// (1) Send the latest tractor ENU position and heading to GenerateImplementPos
		//		Will return corrected ENU values accounting for heading
		// (2) Send the corrected ENU implement values with heading to update spray applied area
		//		This will perfome the logic to either spray the area or not
		UpdateAppliedArea(GenerateImplementPos(tractorPos, heading), heading);
	}


	//-----------------------------------------------------------------------------
	// CImplement::UpdateAppliedArea(...)
	//-----------------------------------------------------------------------------
	void CImplement::UpdateAppliedArea(const CEnuPosition& newImplementPos,
		double heading)
	{
		
		// Get updated L&R ENU Position values and calculate the new polygon if necessary
		CEnuPosition newLPos = getLeftPos(_Width / 2);
		CEnuPosition newRPos = getRightPos(_Width / 2);
		CPolygon newPoly = GeneratePolygon(_currLPos,
			_currRPos,
			newLPos,
			newRPos,
			_Width,
			_numNozzles,
			heading);

		// Turn the nozzles off if the spray polygon overlaps where we've already sprayed
		//bool turnNozzlesOn = !_appliedArea.CheckOverlap(newPoly);
		// Return a hex value to send to a control register on the MCU
		int turnNozzlesOn = _appliedArea.CheckOverlap(newPoly);

		// 
		if (turnNozzlesOn > 0x00)
		{
			// ENU point is not in a sprayed area.
			// Update the poylgon vector
			_appliedArea.AddPolygon(newPoly);
		}

		SetAllNozzles(turnNozzlesOn);

		_isSpraying = turnNozzlesOn;
		_currPos = newImplementPos;
		_currHeading = heading;
		_currRPos = newRPos;
		_currLPos = newLPos;
	}

	CPolygon CImplement::GeneratePolygon(	const CEnuPosition& backLeft, 
											const CEnuPosition& backRight, 
											const CEnuPosition& frontLeft, 
											const CEnuPosition& frontRight,
											const double Width,
											const int numNozzles,
											const double heading
											) const
	{
		CPolygon newPolygon = CPolygon( backLeft, backRight, frontLeft, frontRight, Width, numNozzles, heading);
		return newPolygon.getPolygonVector();
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

	// Return implement offset calculations
	CEnuPosition CImplement::GenerateImplementPos(const CEnuPosition& tractorPos, double heading) const
	{
		// Assume: CEnuPositon correctly provides X,Y,Z in meters
		// TODO: Apply the implement offset values 
		//		(1) Width
		//		(2) DistnaceToImplement
		
	
		// Variables 
		double implementEast = 0.0;
		double implementNorth = 0.0;
		double implementUp = tractorPos.getUp; // Do we care about altitude? 

		// Math
		// TODO: Performe the math to accomidate heading to the established ENU units. 
		// Example that needs testing:
		implementEast = tractorPos.getEast * sin(heading);
		implementNorth = tractorPos.getNorth * cos(heading);
		// More time is needed to add DistanceToImplement with the corrected ENU values
		// Will proable need an extesive rotation and translation matrix for correct calucalations
		
		
		// RETURN: Correct ENU units for the implement accounting for heading
		CEnuPosition implementPos = CEnuPosition(implementEast,implementNorth, implementUp);
		return implementPos;
	}

}

