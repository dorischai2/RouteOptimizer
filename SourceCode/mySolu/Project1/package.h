#pragma once

#include "mapping.h"

/**
* A package contains a weight and size to be added to a truck.
* Sizes should be 1/2 cubic meter, 1 cubic meter, and 5 cubic meters sizes.
* It points to a Point struct which represents the destination of the box specified by a row number and column letter.
*/
struct Package
{
    int weight;
    double size;
    struct Point destination; // no need to be a ptr here
    struct Route deliveryPath; // seem to make sense for the package to hold its delivery path
};
