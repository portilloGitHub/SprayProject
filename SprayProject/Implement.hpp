//============================================================================
/// @file Implement.hpp
///
/// Declares class trimble::CImplement.
///
/// Copyright (c) 2017 Trimble, Inc.
//============================================================================
#ifndef _IMPLEMENT_HPP_
#define _IMPLEMENT_HPP_

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
	  CImplement(double width, double distanceToTractor);

	  // Retrieve configured width and distance to tractor
	  double Width() const { return _Width; }
	  double DistanceToTractor() const { return _DistanceToTractor; }

	  // Retrieves the current position of the implement (center)
	  CEnuPosition Position() const { return _currPos; }

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
		CEnuPosition LeftPos(double distanceFromCenter) const { return _currLPos; }

		// Gets a position to the right of the implement center
		CEnuPosition RightPos(double distanceFromCenter) const { return _currRPos; }

		// Generates a polygon given the where the implement ends were and are now
		CPolygon GeneratePolygon(const CEnuPosition& backLeft,
								 const CEnuPosition& backRight,
								 const CEnuPosition& frontLeft,
								 const CEnuPosition& frontRight) const;

		// Turns all the nozzles on or off so they activly start or stop spraying
		void SetAllNozzles(bool on);

		// Updates the applied area given a new implement position and heading
		void UpdateAppliedArea(const CEnuPosition& newImplementPos, double heading);

	  private:
		const double  _Width;
		const double  _DistanceToTractor;
		double        _currHeading;
		bool          _isSpraying;
		CENUPosition  _currPos;
		CENUPosition  _currLPos;
		CENUPosition  _currRPos;
		CAppliedArea  _appliedArea;
	};


}
#endif

