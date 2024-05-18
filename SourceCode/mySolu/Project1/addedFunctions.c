#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include "addedFunctions.h" 
#include "mapping.h"

//truckLessFull - Two pointers that point to trucks are passed in. 
// The function goes determines which truck is less full and should
// be used in the scenario that two trucks are the same distance away from the destination. 
// It returns:
//  -1 if the trucks are identical, 
//   0 if the second truck is less full and
//   1 if the first truck is less full. 
// 
//It also accounts for the fact that a truck that is at max capacity or weight is automatically full.
int truckLessFull(struct Truck* firstTruck, struct Truck* secondTruck) {

    //Get the percentage of each factor
    double firstWeightPercentage = (double)firstTruck->currentWeight / MAX_WEIGHT;
    double firstCapacityPercentage = (double)firstTruck->currentCapacity / MAX_CAPACITY;
    double secondWeightPercentage = (double)secondTruck->currentWeight / MAX_WEIGHT;
    double secondCapacityPercentage = (double)secondTruck->currentCapacity / MAX_CAPACITY;

    //Check if all values match, indicating these two trucks are identical for some reason
    if (firstTruck->currentWeight == secondTruck->currentWeight &&
        firstTruck->currentCapacity == secondTruck->currentCapacity) {
        return -1;
    }

    //Check if both trucks have maxed out a factor
    if (isTruckFull(firstTruck) && isTruckFull(secondTruck)) {
        //Determine which factors are not maxed out. The non maxed factor will be less than 100%
        double firstNonMax = (firstWeightPercentage < firstCapacityPercentage) ? firstWeightPercentage : firstCapacityPercentage;
        double secondNonMax = (secondWeightPercentage < secondCapacityPercentage) ? secondWeightPercentage : secondCapacityPercentage;
        //Finally compare the non max factors
        return (firstNonMax < secondNonMax) ? 1 : 0;
    }

    //If only the first truck has a max factor, it's automatically more full than the second truck
    if (firstWeightPercentage == 1 || firstCapacityPercentage == 1) {
        return 0;
    }

    //If only the second truck has a max factor, it's automatically more full than the first truck
    if (secondWeightPercentage == 1 || secondCapacityPercentage == 1) {
        return 1;
    }

    //Otherwise from here out if there are no max factors, we directly compare the limiting factors
    double firstLimitingFactor = (firstWeightPercentage < firstCapacityPercentage) ? firstWeightPercentage : firstCapacityPercentage;
    double secondLimitingFactor = (secondWeightPercentage < secondCapacityPercentage) ? secondWeightPercentage : secondCapacityPercentage;

    //Return 1 if the first truck is less full, else return 0
    return (firstLimitingFactor < secondLimitingFactor) ? 1 : 0;
}

//validDestination - This function recieves a pointer to maps and a row and column number representing what the user inputs
// it validates the destination entered and makes sure it's within the bounds of the map and a building that is selected for drop off. 
int validDestination(struct Map* maps, int row, char col)
{
    int result = 0;
    int tempRow = 0;
    int tempCol = 0;
    tempRow = row - 1;
    if (col == 'A' || col == 'B' || col == 'C' || col == 'D' || col == 'E' || col == 'F' || col == 'G' || col == 'H' || col == 'I'
        || col == 'J' || col == 'K' || col == 'L' || col == 'M' || col == 'N' || col == 'O' || col == 'P' || col == 'Q' || col == 'R' ||
        col == 'S' || col == 'T' || col == 'U' || col == 'V' || col == 'W' || col == 'X' || col == 'Y' || col == 'Z') {
        tempCol = col - 'A';
    }
    else {
        tempCol = col - 'a';
    }
    

    if (maps->squares[tempRow][tempCol] == 1)
    {
        result = 1;
    }
    else {
        printf("Invalid destination\n");
    }
    return result;
}

//compareRouteLengths - similarly to truckLessFull, two routes are passed in 
// whichever has the lesser number of points on the map determines which route is shorter. 
// It returns:
// -1 if route 1 is shorter, 
// 1 if route 2 is shorter and 
// 0 if both routes are identical.
int compareRouteLengths(struct Route route1, struct Route route2) {
    if (route1.numPoints < route2.numPoints) {
        // route1 is shorter
        return -1; 
    } else if (route1.numPoints > route2.numPoints) {
        // route2 is shorter
        return 1; 
    } else {
         // both routes have an equal number of points
        return 0; 
    }
}

//validatePackage - A package is passed into this function and it is validated through some if statements to see if it meets the requirements.
// It returns 0 or 1 mimicking boolean values. 
// 1 representing a valid package, 
// 0 otherwise. 
// 
// This ensures that the package weight is greater than 0 and below 1200kg and that size of the box comes in .5, 1 and 5 cubic meters
int validatePackage(struct Package* p)
{
    int valid = 0;
    if (p->weight <= 1200 && p->weight > 0)
    {
        if (fabs(p->size - 0.5) < 0.01 || fabs(p->size - 1) < 0.01 || fabs(p->size - 5) < 0.01)
        {
            valid = 1;
        }
        else {
            printf("Invalid size\n");
            p->size = 0;
        }
    }
    else {
        printf("Invalid weight (must be 1-1200 Kg.)\n");
        p->weight = 0;
    }

    return valid;
}

//Main logic for determining which truck and diversion
//Still need to modularize
int calculateDeliveryRouteForPkg(struct Package* package, struct Truck* blueTruck, struct Truck* greenTruck, struct Truck* yellowTruck, const struct Map* map) {

    //By this point all truck routes are initalized, get shortest path from the closest point to the destination

    package->destination.col -= 'A';

    struct Route blueShortestPath = shortestPath(map, blueTruck->truckRoute.points[getClosestPoint(&blueTruck->truckRoute, package->destination)], package->destination);
    struct Route greenShortestPath = shortestPath(map, greenTruck->truckRoute.points[getClosestPoint(&greenTruck->truckRoute, package->destination)], package->destination);
    struct Route yellowShortestPath = shortestPath(map, yellowTruck->truckRoute.points[getClosestPoint(&yellowTruck->truckRoute, package->destination)], package->destination);
           
    // maybe we should keep an order of shortest path from shortest to longest, just in case if the shortest route truck is not available.
    int firstChoice;
    int secChoice;
    int thirdChoice;

    if (blueShortestPath.numPoints > greenShortestPath.numPoints) {
        if (greenShortestPath.numPoints > yellowShortestPath.numPoints) {
            // blue > green > yellow
            firstChoice = YELLOW;
            secChoice = GREEN;
            thirdChoice = BLUE;
        }
        else if (yellowShortestPath.numPoints > greenShortestPath.numPoints) {
            firstChoice = GREEN;
            if (blueShortestPath.numPoints > yellowShortestPath.numPoints)
                // blue > yellow > green
            {
                secChoice = YELLOW;
                thirdChoice = BLUE;
            }
            else if (yellowShortestPath.numPoints > blueShortestPath.numPoints)
                // yellow > blue > green
            {
                secChoice = BLUE;
                thirdChoice = YELLOW;
            }
            // blue and yellow paths has same length
            else {
                if (truckLessFull(blueTruck, yellowTruck))
                    // if blue truck is less full
                {
                    secChoice = BLUE;
                    thirdChoice = YELLOW;
                }
                else
                {
                    secChoice = YELLOW;
                    thirdChoice = BLUE;
                }
            }
        }
        // green and yellow path has same length (and blue longer than both)
        else {
            thirdChoice = BLUE;
            // if green truck is less full
            if (truckLessFull(greenTruck, yellowTruck))
            {
                firstChoice = GREEN;
                secChoice = YELLOW;
            }
            else
            {
                firstChoice = YELLOW;
                secChoice = GREEN;
            }
        }
    }
    else if (greenShortestPath.numPoints > blueShortestPath.numPoints) {
        if (blueShortestPath.numPoints > yellowShortestPath.numPoints) {
            // green > blue > yellow
            firstChoice = YELLOW;
            secChoice = BLUE;
            thirdChoice = GREEN;
        }
        else if (yellowShortestPath.numPoints > blueShortestPath.numPoints) {
            firstChoice = BLUE;
            if (greenShortestPath.numPoints > yellowShortestPath.numPoints) {
                // green > yellow > blue
                secChoice = YELLOW;
                thirdChoice = GREEN;
            }
            else if (yellowShortestPath.numPoints > greenShortestPath.numPoints) {
                // yellow > green > blue
                secChoice = GREEN;
                thirdChoice = YELLOW;
            }
            else {
                if (truckLessFull(greenTruck, yellowTruck)) {
                    secChoice = GREEN;
                    thirdChoice = YELLOW;
                }
                else {
                    secChoice = YELLOW;
                    thirdChoice = GREEN;
                }
            }
        }
        // blue yellow is the same (and green is longer than both)
        else {
            thirdChoice = GREEN;
            if (truckLessFull(blueTruck, yellowTruck)) {
                firstChoice = BLUE;
                secChoice = YELLOW;
            }
            else {
                firstChoice = YELLOW;
                secChoice = BLUE;
            }
        }
    }
    // green and blue is the same
    else {
        if (yellowShortestPath.numPoints > greenShortestPath.numPoints)
        {   
            // yellow longer than both green & blue will make it last choice
            thirdChoice = YELLOW;
            if (truckLessFull(blueTruck, greenTruck)) {
                firstChoice = BLUE;
                secChoice = GREEN;
            }
            else {
                firstChoice = GREEN;
                secChoice = BLUE;
            }
        }
        else if (greenShortestPath.numPoints > yellowShortestPath.numPoints) {
            // yellow shorter than both green & blue makes it first choice
            firstChoice = YELLOW;
            if (truckLessFull(blueTruck, greenTruck)) {
                secChoice = BLUE;
                thirdChoice = GREEN;
            }
            else {
                secChoice = GREEN;
                thirdChoice = BLUE;
            }
        }
        // IF THEY ARE ALL THE SAME LENGTH FOR SOME REASON
        else {
            if (truckLessFull(blueTruck, greenTruck))
            {
                if (truckLessFull(blueTruck, yellowTruck))
                {
                    firstChoice = BLUE;
                    if (truckLessFull(yellowTruck, greenTruck)) {
                        secChoice = YELLOW;
                        thirdChoice = GREEN;
                    }
                    else {
                        secChoice = GREEN;
                        thirdChoice = YELLOW;
                    }
                }
                else {
                    firstChoice = YELLOW;
                    secChoice = BLUE;
                    thirdChoice = GREEN;
                }
            }
            else {
                if (truckLessFull(greenTruck, yellowTruck))
                {
                    firstChoice = GREEN;
                    if (truckLessFull(yellowTruck, blueTruck))
                    {
                        secChoice = YELLOW;
                        thirdChoice = BLUE;
                    }
                    else {
                        secChoice = BLUE;
                        thirdChoice = YELLOW;
                    }
                }
                else {
                    firstChoice = YELLOW;
                    secChoice = GREEN;
                    thirdChoice = BLUE;
                }
            }
        }
    }

    //Once shortest paths are determined, just need to validate truck and add package and validate the addition of package to truck
    int truckFound = addPackageToSelectedTruck(blueTruck, yellowTruck, greenTruck, firstChoice, package);
    if (!truckFound) {
        addPackageToSelectedTruck(blueTruck, yellowTruck, greenTruck, secChoice, package);
    }

    if (!truckFound) {
        addPackageToSelectedTruck(blueTruck, yellowTruck, greenTruck, thirdChoice, package);
    }

    // I think we return a int indicating whether a delivery path was found. If not, specs states it will be delivered next day
    return truckFound;
}


//Getter function to query a trucks stats
int isTruckFull(struct Truck* truck) {
    return (truck->currentCapacity >= MAX_CAPACITY || truck->currentWeight >= MAX_WEIGHT);
}

//Setter function to modify a trucks stats
int addPackageToTruck(struct Truck* truck, struct Package* pkg) {
    int success = 0;
    if (!isTruckFull(&truck)) {
        if (truck->currentCapacity + pkg->size <= MAX_CAPACITY && truck->currentWeight + pkg->weight <= MAX_WEIGHT) {
            truck->currentCapacity += pkg->size;
            truck->currentWeight += pkg->weight;
            success = 1;
        }
    }
    return success;
}

int addPackageToSelectedTruck(struct Truck* blueTruck, struct Truck* yellowTruck, struct Truck* greenTruck, int choice, struct Package* package)
{
    int truckFound = 0;
    switch (choice)
    {
    case BLUE:
        if (addPackageToTruck(blueTruck, package))
        {
            printf("Ship on BLUE LINE\n");
            truckFound = 1;
        }
        break;

    case YELLOW:
        if (addPackageToTruck(yellowTruck, package))
        {
            printf("Ship on YELLOW LINE\n");
            truckFound = 1;
        }
        break;

    case GREEN:
        if (addPackageToTruck(greenTruck, package))
        {
            printf("Ship on GREEN LINE\n");
            truckFound = 1;
        }
        break;
    }

    return truckFound;
}


int validInput(struct Map* baseMap, int row, char col, struct Package* pkg) {
    return(validDestination(baseMap, row, col) && validatePackage(pkg));
}

void menuMain(struct Map* baseMap, struct Package* pkg, struct Map* routeMap, struct Truck* blueTruck, struct Truck* greenTruck, struct Truck* yellowTruck) {
    
    //Local variables for user input 
    int weight;
    double boxSize;
    int row;
    char col;
   
    //Flag 
    int valid = 0;

    printMap(routeMap, 1, 1);
    printf("=================\n");
    printf("Seneca College Deliveries\n");
    printf("=================\n");

    do
    {
        printf("Enter shipment weight, box size and destination (0 0 x to stop): ");
        scanf("%d %lf %d %c", &weight, &boxSize, &row, &col);
        
        pkg->size = boxSize;
        pkg->weight = weight;

        if (validInput(baseMap, row, col, pkg)) {

            //pkg->destination.row = row + '0';
            pkg->destination.row = row;
            pkg->destination.col = col;
            if (calculateDeliveryRouteForPkg(pkg, blueTruck, greenTruck, yellowTruck, baseMap)) {

                
                
                //Just testing out printing routes but need to print out a variable which holds the selected path
                //Maybe calculateDelivery should return a route which holds the truck selected
                for (int i = 0; i < greenTruck->truckRoute.numPoints; i++) {
                    printf("%d%c", greenTruck->truckRoute.points[i].row + 1, 'A' + greenTruck->truckRoute.points[i].col);
                    printf(", ");
                }
                printf("\n");
            }
        }
                
    } while (!valid);

    printf("Thanks for shipping with Seneca!\n");
}
