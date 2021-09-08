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
		// (1) Position of the tractor
		// (2) Speed
		// (3) Heading
		
		// (1) Tractor Position
		// Assumption: The listiner is the means to get data from another part ofthe program.
		//				In this case, the listener will return formated xyz data from a section
		//				That deals with the GPS reciever. That reciever code will have the 
		//				necessary filters and algorithims to process raw xyz or lla data.
		//				CEnuPosition _pos should get these values.
		//				_pos is the latest tractor position information
		_pos.FromXYZ(<lla> or <enu> data from some other part of the code);

		// (2) Speed 
		// Replace 0.0 with real speed data from CAN bus or ENU distance over time calculations
		// Could ALSO provide speed if using 
		//	an industry NMEA message
		_speed = <data from CANbus or displacement calcuations or NMEA message>;

		// (3) Heading
		// Calculate heading using Haversine formula
		// GPS code section could ALSO provide heading already if using 
		//	an industry NMEA message
		_heading = <Haversine formula or similar>;

	}
}
