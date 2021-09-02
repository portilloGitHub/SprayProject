//============================================================================
/// @file Tractor.hpp
///
/// Declares class trimble::CTractor.
///
/// Copyright (c) 2017 Trimble, Inc.
//============================================================================
#ifndef _TRACTOR_HPP_
#define _TRACTOR_HPP_

#include <set>
#include "EnuPosition.hpp"

namespace trimble
{


//-----------------------------------------------------------------------------
// Listener Interface
//-----------------------------------------------------------------------------
class ITractorPositionListener
{
public:
  virtual void HandleNewTractorPosition(const CEnuPosition& tractorPos,
                                        double heading) = 0;
};


//-----------------------------------------------------------------------------
// Class
//-----------------------------------------------------------------------------
class CTractor
{
public:
  CTractor();

  // Retrieves the current speed of the tractor (in m/s)
  double Speed() const { return _speed; }

  // Get heading of tractor (in radians)
  double Heading() const { return _heading; }

  // Retrieves the position of the tractor
  CEnuPosition Position() const { return _pos; }

  // Register/unregister listener for the tractor position.
  void RegisterListener(ITractorPositionListener* listener);
  void UnregisterListener(ITractorPositionListener* listener);

  // Must be called at regular interval
  void PeriodicUpdate();

private:
  void NotifyListeners(const CEnuPosition& tractorPos, double heading);

  double _speed;
  double _heading;
  CEnuPosition _pos;

  typedef std::set<ITractorPositionListener*> CListenerSet;
  CListenerSet _listeners;
};


}
#endif

