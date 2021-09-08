//===========================================================================
/// @file EnuPosition.cpp
///
/// Implements class trimble::CEnuPosition.
///
/// Copyright (c) 2017 Trimble, Inc.
//===========================================================================

#include "EnuPosition.hpp"
#include "XyzPos.hpp"
#include "CLlaPos.hpp"

namespace trimble
{
	void CEnuPosition::FromXYZ(const CXyzPos& xyzPos)
	{
		// Set the _est, _north, _up units 
		_east = xyzPos.getEastValue();
		_north = xyzPos.getNorthValue();
		_up = xyzPos.getUpValue();
	}

	void CEnuPosition::FromLLA(const CXyzPos& llaPos)
	{
		// Assumption: We want to convert lla to ENU 
		_east = convertLLAtoENU_E(llaPos);
		_north = convertLLAtoENU_E(llaPos);
		_up = convertLLAtoENU_E(llaPos);
	}

	double CEnuPosition::convertLLAtoENU_E(const CLlaPos& llaPos)
	{
		double east = 0.0;
		// Convert LLA units to ENU
		return east;
	}

	double CEnuPosition::convertLLAtoENU_N(const CLlaPos& llaPos)
	{
		double north = 0.0;
		// Convert LLA units to ENU
		return north;
	}

	double CEnuPosition::convertLLAtoENU_U(const CLlaPos& llaPos)
	{
		double up = 0.0;
		// Convert LLA units to ENU
		return up;
	}
}