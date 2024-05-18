#pragma once
#include <stdio.h>
#include "mapping.h"
#include "truck.h"
#include "package.h"

/* proposed functions: //rough draft
// set a certain truct to one of the three routes
void setTruckRoute(struct Route* r, struct Truck* t);

// add a valid package to the truck
void addPackageToTruck(struct Package p, struct Truck* t);

// update the current location of the truck
void updateTruckLocation(struct Point pt, struct Truck* t);
*/

//Selected functions for MS3

/*
*  Determines which truck has more space remaining as a percentage, considering the limiting factor as a percentage
* @param truck - the first truck to query for current weight AND current capacity
* @param truck - the second truck to query for current weight AND current capacity
* @returns - int type returns
* (1)the first truck has more available space
* or (0)the second truck has more available space
* or (-1)the trucks have an equal percentage of available space
*/
int truckLessFull(struct Truck* firstTruck, struct Truck* secondTruck);

/*
*  To check the destination validation
* @param map : the data of map
* @param row : the row number
* @param row : the column location
* @returns - int type returns
* (1)the destination is valid
* or (0)the destination is invalid
*/
int validDestination(struct Map* maps, int row, char col);

/*
* Compares the lengths of two routes and determines which route is shorter.
* @param route1 : the first route to compare.
* @param route2 : the second route to compare.
* @returns - int type returns
* (-1) if the route1 is shorter,
* (1) if the route2 is shorter,
* (0) if both routes are of equal length.
*/
int compareRouteLengths(struct Route route1, struct Route route2);

/*
* For given package, check if the package meets dimensional and weight requirements.
* @param p: package to be checked
* @returns 0 or 1 mimicking boolean values
* (0) if package does not meet the requirement
* (1) if package is a valid package
*/
int validatePackage(struct Package* p);

/*
* find the path to delivery the package
* @param package: the package that need to be delivered
* @returns a struct Route type representing the path to delivery the package to destination
*/
int calculateDeliveryRouteForPkg(struct Package* package, struct Truck* blueTruck, struct Truck* greenTruck, struct Truck* yellowTruck, const struct Map* map);

/*
* Query method for determining if a truck has reached max capacity
* @param truck: a truck to query
* @returns an int representing true or false
*/
int isTruckFull(struct Truck* truck);

/*
* Modifier method to add a package to a trucks weight and capacity
* @param truck: truck to modify
* @param pkg: package to add to truck
* @returns nothing
*/
int addPackageToTruck(struct Truck* truck, struct Package* pkg);

/*
* Modifier method to add a package to the truck based on selected choice
* @param trucks: pointers to three trucks
* @param choice: representing the selected truck
* @param package: pointer to the package to be added
* @returns 1 is package is added, 0 if package cannot be added to the selected truck
*/
int addPackageToSelectedTruck(struct Truck* blueTruck, struct Truck* yellowTruck, struct Truck* greenTruck, int choice, struct Package* package);

/*
* Entry point into main logic of program
* @param baseMap: map to display
* @param initalPkg: an empty package with no specifications passed in
* @param routeMap: map to display with a specific route on it
* param blueTruck: blue truck structure with all it's data
* param greenTruck: blue truck structure with all it's data
* param yellowTruck: blue truck structure with all it's data
* @returns nothing
*/

void menuMain(struct Map* baseMap, struct Package* initalPkg, struct Map* routeMap, struct Truck* blueTruck, struct Truck* greenTruck, struct Truck* yellowTruck);

int validInput(struct Map* baseMap, int row, char col, struct Package* pkg);