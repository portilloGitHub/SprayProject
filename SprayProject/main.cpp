/**
* Simulation entry point
**/

#include <chrono>
#include <thread>
#include "Implement.hpp"

using namespace trimble;

// Width = 120
// Distance to tractor = 5
// numOfSprayValves = 12
// 
// Placeholder for testing:
// TODO: These values should be pulled from a table or database in real life
static CTractor tractor = CTractor();
static CImplement implement = CImplement(120,5,12);


int main()
{
	// (1) Implement is calibrated with Boom width 120 and distance to tractor at 5
	// Infinite loop to monitor current position

	for (;;)
	{
		// Keep updating vehicle every 5Hz
		
		tractor.PeriodicUpdate(); // Update speed / heading / ENU data for truck		
		implement.HandleNewTractorPosition(tractor.Position(), tractor.Heading()); // Apply ENU data to implement with offsets an handle the spray logic

		// Represent a 200ms cylce.
		// In practice, this should be handled by the listener class and some 
		//		sort of scheduler or RTOS management system 
	}
	return 0;
}