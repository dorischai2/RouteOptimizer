#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "mapping.h"
#include"addedFunctions.h"

int main(void)
{
	struct Map baseMap = populateMap();

	// Initalize our trucks
	struct Truck blueTruck = { 0 };
	struct Truck greenTruck = { 0 };
	struct Truck yellowTruck = { 0 };

	// Initialize truck with associated routes
	blueTruck.truckRoute = getBlueRoute();
	greenTruck.truckRoute = getGreenRoute();
	yellowTruck.truckRoute = getYellowRoute();

	//Initialize a package
	struct Package pkg = { 0 };

	struct Map routeMap = addRoute(&baseMap, &blueTruck.truckRoute);
	routeMap = addRoute(&baseMap, &greenTruck.truckRoute);
	routeMap = addRoute(&baseMap, &yellowTruck.truckRoute);

	menuMain(&baseMap, &pkg, &routeMap, &blueTruck, &greenTruck, &yellowTruck);

	return 0;
}
