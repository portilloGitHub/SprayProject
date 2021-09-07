//============================================================================
/// @file Implement.hpp
///
/// Declares class trimble::CImplement.
///
/// Description: Class to handle implement functionality
///
/// Copyright (c) 2017 Trimble, Inc.
//============================================================================
#ifndef _IMPLEMENT_HPP_
#define _IMPLEMENT_HPP_

#include <stdio.h>

#include "EnuPosition.hpp"
#include "AppliedArea.hpp"
#include "Tractor.hpp"

namespace trimble
{
	//-----------------------------------------------------------------------------
	// Class
	//-----------------------------------------------------------------------------
	class CImplement : public ITractorPositionListener
	{
	public:
	  CImplement(double width, double distanceToTractor, int numNozzles);

	  // Retrieve configured width and distance to tractor
	  double Width() const { return _Width; }
	  double DistanceToTractor() const { return _DistanceToTractor; }

	  // Retrieves the current position of the implement (center)
	  CEnuPosition getPosition() const { return _currPos; }

	  // Retrieve the area where spray has been applied
	  const CAppliedArea& AppliedArea() const { return _appliedArea; }

	  // Indicates whether or not the implement is currently spraying
	  bool IsSpraying() const { return _isSpraying; }

	  // ITractorPositionListener method
	  virtual void HandleNewTractorPosition(const CEnuPosition& tractorPos,
											double heading);

	protected:
		// Generates the center position of the implement given the tractor pos
		CEnuPosition GenerateImplementPos(const CEnuPosition& tractorPos,
										  double heading) const;

		// Gets a position to the left of the implement center
		CEnuPosition getLeftPos(double distanceFromCenter) const { return _currLPos;  }

		// Gets a position to the right of the implement center
		CEnuPosition getRightPos(double distanceFromCenter) const { return _currRPos; }

		// Generates a polygon given the where the implement ends were and are now
		CPolygon GeneratePolygon(const CEnuPosition& backLeft,
								 const CEnuPosition& backRight,
								 const CEnuPosition& frontLeft,
								 const CEnuPosition& frontRight,
								 const double width,
								 const int numNozzles,
								 const double heading) const;

		// Turns all the nozzles on or off so they activly start or stop spraying
		void SetAllNozzles(bool on);

		// Updates the applied area given a new implement position and heading
		void UpdateAppliedArea(const CEnuPosition& newImplementPos, double heading);

	  private:
		const double  _Width;
		const double  _DistanceToTractor;
		double        _currHeading;
		bool          _isSpraying;
		int			  _numNozzles;

		// Upon decleration, _currPos / _currLPos / _currRPos
		// are set to the current ENU coordinates received from the 
		// GPS receiver.
		// The data is stored in a vector -> 
		// UpdateAppliedArea() updates the class object
		// Format: East / North / Up
		CEnuPosition  _currPos;
		CEnuPosition  _currLPos;
		CEnuPosition  _currRPos;

		// 
		CAppliedArea  _appliedArea;
	};


}
#endif

