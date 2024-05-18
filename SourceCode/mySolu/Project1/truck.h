#pragma once

#include "mapping.h"
#include "package.h"

#define MAX_WEIGHT 1200
#define MAX_CAPACITY 50
#define MAX_DELIVERIES 100 // set to 100 (50 / 0.5) for now

/**
* A truck is able to carry up to 1200 kg of weight and 50 cubic meter of capacity.
* It contains information about the packages, it's route from the first point to last,
* and it's current row-column position.
*/
struct Truck
{
    int currentWeight; //Changed it to current weight/capacity as this will make calculations easier rather than available weight/capacity
    double currentCapacity;
    struct Package packages[MAX_DELIVERIES];
    struct Route truckRoute;
    struct Point currentLocation;
};


