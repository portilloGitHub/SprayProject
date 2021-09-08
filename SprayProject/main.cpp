/**
* Simulation entry point to test trimble api
**/

#include <chrono>
#include <thread>
#include "Implement.hpp"

using namespace trimble;

// Width = 120
// Distance to tractor = 5
// Placeholder for testing:
// TODO: These values should be pulled from a table or database
static CTractor tractor = CTractor();
static CImplement implement = CImplement(120,5,12);


int main()
{
	// (1) Implement is calibrated with Boom width 120' and distance to tractor at 5'
	// (2) Implement sends command to handle new tractor position and heading 
	// Infinite loop to monitor current position

	for (;;)
	{
		// Keep updating vehicle every 5Hz
		
		tractor.PeriodicUpdate();
		implement.HandleNewTractorPosition(tractor.Position(), tractor.Heading());

		// Represent a 200ms cylce.
		// In practice, this should be handled by the listener class and some 
		//		sort of scheduler or RTOS management system 

		std::this_thread::sleep_for(std::chrono::microseconds(200)); // Windows C++ method. this will change for other platforms.
	}
	return 0;
}