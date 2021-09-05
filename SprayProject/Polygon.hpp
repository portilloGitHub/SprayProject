//============================================================================
/// @file Polgon.hpp
///
/// Declares class trimble::CPolygon.
///
/// Copyright (c) 2021 Trimble, Inc.
//============================================================================
#ifndef _POLYGON_HPP_
#define _POLYGON_HPP_

#include "EnuPosition.hpp"

namespace trimble
{

	//-----------------------------------------------------------------------------
	// Class
	//-----------------------------------------------------------------------------
	class CPolygon
	{

	public:
		CPolygon();

		CPolygon(const CEnuPosition& oldLeft,
			const CEnuPosition& oldRight,
			const CEnuPosition& newLeft,
			const CEnuPosition& newRight,
			int numNozzles) :
			_oldLeft(oldLeft),
			_oldRight(oldRight),
			_newLeft(newLeft),
			_newRight(newRight),
			_numNozzles(numNozzles) {};

		CPolygon getArea();


	private:
		CEnuPosition _oldLeft;
		CEnuPosition _oldRight;
		CEnuPosition _newLeft;
		CEnuPosition _newRight;
		int _numNozzles;
	};
}

#endif
