/**
* Simulation entry point to test trimble api
**/

#include "Implement.hpp"

using namespace trimble;


int main()
{
	double boomWidth = 120; // Feet
	double distanceToTractor = 5; // Feet
	CImplement implement = CImplement(boomWidth, distanceToTractor); // Create the tractor instance

	return 0;
}