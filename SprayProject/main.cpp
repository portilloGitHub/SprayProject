/**
* Simulation entry point to test trimble api
**/

#include "Implement.hpp"

using namespace trimble;

// Width = 120
// Distance to tractor = 5
// Placeholder for testing:
// TODO: These values should be pulled from a table or database
static CImplement implement = CImplement(120,5);


int main()
{
	// Infinite loop to monitor current position and
	//	control spray nozels 
	for (;;)
	{
		// TODO: add timmer for 5Hz (~200ms)
	}
	return 0;
}