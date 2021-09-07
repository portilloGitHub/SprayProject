//===========================================================================
/// @file Tractor.cpp
///
/// Implements class trimble::CTractor.
///
/// Copyright (c) 2017 Trimble, Inc.
//===========================================================================

#include "Tractor.hpp"

namespace trimble
{
	void trimble::CTractor::PeriodicUpdate()
	{
		// This section updates the following:
		// (1) Speed
		// (2) Heading
		// (3) Position of the tractor
		
		// (1) Speed 
		// Replace 0.0 with real speed data from CAN bus or distance over time calculations
		// using CEnuPosition data
		_speed = 0.0;

		// (2) Heading
		// Get heading from two CEnuPosition units
		_heading = 0.0;
	}
}
